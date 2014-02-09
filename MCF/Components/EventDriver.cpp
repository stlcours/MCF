// 这个文件是 MCF 的一部分。
// 有关具体授权说明，请参阅 MCFLicense.txt。
// Copyleft 2014. LH_Mouse. All wrongs reserved.

#include "../StdMCF.hpp"
#include "EventDriver.hpp"
#include "../Core/CriticalSection.hpp"
#include <memory>
#include <map>
#include <list>
#include <functional>
#include <climits>
using namespace MCF;

namespace {
	typedef std::shared_ptr<std::function<bool(std::uintptr_t)>> PHANDLER_PROC;
	typedef std::list<PHANDLER_PROC> HANDLER_LIST;
	typedef std::shared_ptr<const HANDLER_LIST> PCHANDLER_LIST;
	typedef std::shared_ptr<HANDLER_LIST> PHANDLER_LIST;

	// 使用 Copy-On-Write 策略。
	CriticalSection g_csWriteLock;
	CriticalSection g_csReadLock;
	std::map<std::uintptr_t, PCHANDLER_LIST> g_mapDelegates;
}

namespace MCF {

namespace __MCF {
	void UnregisterEventHandler(const EVENT_HANDLER_HANDLE &Handle) noexcept {
		if(!Handle.second){
			return;
		}
		CRITICAL_SECTION_SCOPE(g_csWriteLock){
			PCHANDLER_LIST *ppList = nullptr;
			CRITICAL_SECTION_SCOPE(g_csReadLock){
				const auto itList = g_mapDelegates.find(Handle.first);
				if(itList != g_mapDelegates.end()){
					ppList = &(itList->second);
				}
			}
			if(ppList && *ppList){
				PHANDLER_LIST pNewList(new HANDLER_LIST(**ppList));
				for(auto it = pNewList->cbegin(); it != pNewList->cend(); ++it){
					if(it->get() == Handle.second){
						pNewList->erase(it);
						break;
					}
				}
				CRITICAL_SECTION_SCOPE(g_csReadLock){
					const auto itList = g_mapDelegates.find(Handle.first);

					ASSERT(itList != g_mapDelegates.end());

					if(pNewList->empty()){
						g_mapDelegates.erase(itList);
					} else {
						itList->second = std::move(pNewList);
					}
				}
			}
		}
	}
}

EventHandlerHolder RegisterEventHandler(std::uintptr_t uEventId, std::function<bool(std::uintptr_t)> fnHandler){
	EventHandlerHolder Holder;
	CRITICAL_SECTION_SCOPE(g_csWriteLock){
		PCHANDLER_LIST *ppList;
		CRITICAL_SECTION_SCOPE(g_csReadLock){
			ppList = &g_mapDelegates[uEventId];
		}
		PHANDLER_LIST pNewList(*ppList ? new HANDLER_LIST(**ppList) : new HANDLER_LIST());
		pNewList->emplace_front(new auto(std::move(fnHandler)));
		const auto pRaw = pNewList->front().get();
		CRITICAL_SECTION_SCOPE(g_csReadLock){
			*ppList = std::move(pNewList);
		}
		Holder = std::make_pair(uEventId, pRaw);
	}
	return std::move(Holder);
}
void RaiseEvent(std::uintptr_t uEventId, std::uintptr_t uContext){
	PCHANDLER_LIST pList;
	CRITICAL_SECTION_SCOPE(g_csReadLock){
		const auto itList = g_mapDelegates.find(uEventId);
		if(itList != g_mapDelegates.end()){
			pList = itList->second;
		}
	}
	if(pList){
		for(const auto &pHandler : *pList){
			if((*pHandler)(uContext)){
				break;
			}
		}
	}
}

}

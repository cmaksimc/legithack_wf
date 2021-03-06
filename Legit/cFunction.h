#pragma once
#include "cClasess.h"

bool IsMyTeam(IActor* mIActor, IActor* eIActor)
{
	INT m_team = IGameFramework::Singleton()->GetIGameRules()->GetTeam(mIActor->m_pEntity->GetId());
	INT e_team = IGameFramework::Singleton()->GetIGameRules()->GetTeam(eIActor->m_pEntity->GetId());

	if (m_team != e_team || e_team == 0)
		return true;
	else
		return false;
}

void function()
{
	SSystemGlobalEnvironment* g_pEnv = SSystemGlobalEnvironment::Singleton();
	IActor* m_pActor = nullptr;

	if (IGameFramework* g_pGame = IGameFramework::Singleton())
	{
		if (ICVar* g_pCvar = ICVar::Singleton())
		{
			if (g_pGame->GetClientActor(&m_pActor))
			{
				m_pActor->Set(IActor_DATA::claymore_detector_radius, 999);

				g_pCvar->Set(ICVar_DATA::i_pelletsDisp, 999.f);
				g_pCvar->Set(ICVar_DATA::cl_fov, 90.f);


				IEntityIt* pEntityIt = g_pEnv->GetIEntitySystem()->GetEntityIterator();

				while (IEntity* m_pEntity = pEntityIt->Next())
				{
					IEntityProxy* pEntityProxy = m_pEntity->GetProxy(ENTITY_PROXY_RENDER);
					if (!pEntityProxy) continue;

					if (IActor* pActor = g_pGame->m_pActorSystem->GetActor(m_pEntity->GetId()))
					{
						if (!IsMyTeam(m_pActor, pActor)) continue;

						pEntityProxy->SetHUDSilhouettesParams(255, 255, 0, 0);
					}
				}
			}
		}
	}
}

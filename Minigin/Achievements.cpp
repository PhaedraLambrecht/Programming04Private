#include "Achievements.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <debugapi.h>
#include <iostream>

namespace dae
{
    Achievements::Achievements(const Achievement& achievement)
        : m_Achievement{achievement}
        ,m_AppID{ SteamUtils()->GetAppID()}
        ,m_bInitialized{ RequestStats()}
    {
        if (m_bInitialized)
        {
            // If initialization is successful, check if the achievement has been achieved
            SteamUserStats()->GetAchievement(m_Achievement.m_pchAchievementID, &m_Achievement.m_bAchieved);
        }
    }

    Achievements::~Achievements()
    {
        std::cout << "Achievements\n";
    }


    bool Achievements::RequestStats() 
    {
        // Check if Steam user stats and user are available/logged in
        if (!SteamUserStats() || !SteamUser() || !SteamUser()->BLoggedOn())
        {
            return false;
        }

        return SteamUserStats()->RequestCurrentStats();
    }

    bool Achievements::SetAchievement()
    {
        // Check if not initialized
        if (!m_bInitialized)
        {
            return false;
        }

        // Set the achievement and store stats
        SteamUserStats()->SetAchievement(m_Achievement.m_pchAchievementID);
        return SteamUserStats()->StoreStats();
    }
    
    // Function to check if the achievement has been received
    void Achievements::HasReceivedAchievement(bool& hasAchieved)
    {
        if (m_bInitialized)
        {
            SteamUserStats()->GetAchievement(m_Achievement.m_pchAchievementID, &hasAchieved);
        }
    }

    void Achievements::ClearAchievement()
    {
        SteamUserStats()->ClearAchievement(m_Achievement.m_pchAchievementID);
    }

}
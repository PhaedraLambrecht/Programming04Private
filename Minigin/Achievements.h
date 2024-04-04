#pragma once
#pragma warning(push)
#pragma warning(disable: 4996)
#include <isteamuserstats.h>
#include <steam_gameserver.h>
#pragma warning(pop)
#include <stdint.h>
#include <vector>
#include <string>


// Based on https://partner.steamgames.com/doc/features/achievements/ach_guide
namespace dae
{
    enum class AchievementID
    {
        ACH_WIN_ONE_GAME
    };

    struct Achievement
    {
        AchievementID m_eAchievementID;
        const char* m_pchAchievementID;
        char m_rgcName[128]{};
        char m_rgcDescription[256]{};
        bool m_bAchieved{};
        int m_iIconImage{};
    };

    class Achievements 
    {
    public:

        Achievements(const Achievement& achievement);
        virtual ~Achievements();

        // Copy and move
        Achievements(const Achievements& other) = delete;
        Achievements(Achievements&& other) = delete;
        Achievements& operator=(const Achievements& other) = delete;
        Achievements& operator=(Achievements&& other) = delete;




        bool RequestStats();
        bool SetAchievement();
        void HasReceivedAchievement(bool& hasAchieved);
        void ClearAchievement();


    private:

        uint64_t m_AppID{ 0 };
        Achievement m_Achievement;
        bool m_bInitialized;// Have we called Request stats and received the callback?
    };

}

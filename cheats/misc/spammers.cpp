// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "spammers.h"

void spammers::clan_tag()
{
	auto apply = [](const char* tag) -> void
	{
		using Fn = int(__fastcall*)(const char*, const char*);
		static auto fn = reinterpret_cast<Fn>(util::FindSignature(crypt_str("engine.dll"), crypt_str("53 56 57 8B DA 8B F9 FF 15")));

		fn(tag, tag);
	};

	static auto removed = false;

	if (!g_cfg.misc.clantag_spammer && !removed)
	{
		removed = true;
		apply(crypt_str(""));
		return;
	}

	if (g_cfg.misc.clantag_spammer)
	{
		auto nci = m_engine()->GetNetChannelInfo();

		if (!nci)
			return;

		static auto time = -1;

		auto ticks = TIME_TO_TICKS(nci->GetAvgLatency(FLOW_OUTGOING)) + (float)m_globals()->m_tickcount; //-V807
		auto intervals = 0.5f / m_globals()->m_intervalpertick;

		auto main_time = (int)(ticks / intervals) % 22;

		if (main_time != time && !m_clientstate()->iChokedCommands)
		{
			auto tag = crypt_str("");

			switch (main_time)
			{
			case 0:
				tag = crypt_str(" ");
				break;
			case 1:
				tag = crypt_str("g ");
				break;
			case 2:
				tag = crypt_str("ga ");
				break;
			case 3:
				tag = crypt_str("gam ");
				break;
			case 4:
				tag = crypt_str("game ");
				break;
			case 5:
				tag = crypt_str("games ");
				break;
			case 6:
				tag = crypt_str("gamese ");
				break;
			case 7:
				tag = crypt_str("gamesen ");
				break;
			case 8:
				tag = crypt_str("gamesens ");
				break;
			case 9:
				tag = crypt_str("gamesense ");
				break;
			case 10:
				tag = crypt_str("gamesense ");
				break;
			case 11:
				tag = crypt_str("amesense ");
				break;
			case 12:
				tag = crypt_str("mesense ");
				break;
			case 13:
				tag = crypt_str("esense ");
				break;
			case 14:
				tag = crypt_str("sense ");
				break;
			case 15:
				tag = crypt_str("ense ");
				break;
			case 16:
				tag = crypt_str("nse ");
				break;
			case 17:
				tag = crypt_str("se ");
				break;
			case 18:
				tag = crypt_str("e ");
				break;
			}

			apply(tag);
			time = main_time;
		}

		removed = false;
	}
}

void spammers::clan_tag_pastesense()
{
	auto apply = [](const char* tag) -> void
	{
		using Fn = int(__fastcall*)(const char*, const char*);
		static auto fn = reinterpret_cast<Fn>(util::FindSignature(crypt_str("engine.dll"), crypt_str("53 56 57 8B DA 8B F9 FF 15")));

		fn(tag, tag);
	};

	static auto removed = false;

	if (!g_cfg.misc.clantag_spammer_pastesense && !removed)
	{
		removed = true;
		apply(crypt_str(""));
		return;
	}

	if (g_cfg.misc.clantag_spammer_pastesense)
	{
		auto nci = m_engine()->GetNetChannelInfo();

		if (!nci)
			return;

		static auto time = -1;

		auto ticks = TIME_TO_TICKS(nci->GetAvgLatency(FLOW_OUTGOING)) + (float)m_globals()->m_tickcount; //-V807
		auto intervals = 0.5f / m_globals()->m_intervalpertick;

		auto main_time = (int)(ticks / intervals) % 22;

		if (main_time != time && !m_clientstate()->iChokedCommands)
		{
			auto tag = crypt_str("");

			switch (main_time)
			{
			case 0:
				tag = crypt_str(" ");
				break;
			case 1:
				tag = crypt_str("p ");
				break;
			case 2:
				tag = crypt_str("pa ");
				break;
			case 3:
				tag = crypt_str("pas ");
				break;
			case 4:
				tag = crypt_str("past ");
				break;
			case 5:
				tag = crypt_str("paste ");
				break;
			case 6:
				tag = crypt_str("pastes ");
				break;
			case 7:
				tag = crypt_str("pastese ");
				break;
			case 8:
				tag = crypt_str("pastesen ");
				break;
			case 9:
				tag = crypt_str("pastesens ");
				break;
			case 10:
				tag = crypt_str("pastesense ");
				break;
			case 11:
				tag = crypt_str("pastesense ");
				break;
			case 12:
				tag = crypt_str("astesense ");
				break;
			case 13:
				tag = crypt_str("stesense ");
				break;
			case 14:
				tag = crypt_str("tesense ");
				break;
			case 15:
				tag = crypt_str("esense ");
				break;
			case 16:
				tag = crypt_str("sense ");
				break;
			case 17:
				tag = crypt_str("ense ");
				break;
			case 18:
				tag = crypt_str("nse ");
				break;
			case 19:
				tag = crypt_str("se ");
				break;
			case 20:
				tag = crypt_str("e ");
				break;
			case 21:
				tag = crypt_str(" ");
				break;
			}

			apply(tag);
			time = main_time;
		}

		removed = false;
	}
}

void spammers::clan_tag_unlucky()
{
	auto apply = [](const char* tag) -> void
	{
		using Fn = int(__fastcall*)(const char*, const char*);
		static auto fn = reinterpret_cast<Fn>(util::FindSignature(crypt_str("engine.dll"), crypt_str("53 56 57 8B DA 8B F9 FF 15")));

		fn(tag, tag);
	};

	static auto removed = false;

	if (!g_cfg.misc.clantag_spammer_unlucky && !removed)
	{
		removed = true;
		apply(crypt_str(""));
		return;
	}

	if (g_cfg.misc.clantag_spammer_unlucky)
	{
		auto nci = m_engine()->GetNetChannelInfo();

		if (!nci)
			return;

		static auto time = -1;

		auto ticks = TIME_TO_TICKS(nci->GetAvgLatency(FLOW_OUTGOING)) + (float)m_globals()->m_tickcount; //-V807
		auto intervals = 0.35f / m_globals()->m_intervalpertick;

		auto main_time = (int)(ticks / intervals) % 33;

		if (main_time != time && !m_clientstate()->iChokedCommands)
		{
			auto tag = crypt_str("");

			switch (main_time)
			{
			case 0:
				tag = crypt_str(" ");
				break;
			case 1:
				tag = crypt_str("♣ ");
				break;
			case 2:
				tag = crypt_str("♣♣ ");
				break;
			case 3:
				tag = crypt_str("♣U♣ ");
				break;
			case 4:
				tag = crypt_str("♣Un♣ ");
				break;
			case 5:
				tag = crypt_str("♣Unl♣ ");
				break;
			case 6:
				tag = crypt_str("♣Unlu♣ ");
				break;
			case 7:
				tag = crypt_str("♣Unluc♣ ");
				break;
			case 8:
				tag = crypt_str("♣Unluck♣ ");
				break;
			case 9:
				tag = crypt_str("♣Unlucky♣ ");
				break;
			case 10:
				tag = crypt_str("♣UnluckyC♣ ");
				break;
			case 11:
				tag = crypt_str("♣UnluckyCh♣ ");
				break;
			case 12:
				tag = crypt_str("♣UnluckyCha♣ ");
				break;
			case 13:
				tag = crypt_str("♣UnluckyChar♣ ");
				break;
			case 14:
				tag = crypt_str("♣UnluckyCharm♣ ");
				break;
			case 15:
				tag = crypt_str("♣UnluckyCharms♣ ");
				break;
			case 16:
				tag = crypt_str("♣UnluckyCharms♣ ");
				break;
			case 17:
				tag = crypt_str("♣UnluckyCharm♣ ");
				break;
			case 18:
				tag = crypt_str("♣UnluckyChar♣ ");
				break;
			case 19:
				tag = crypt_str("♣UnluckyCha♣ ");
				break;
			case 20:
				tag = crypt_str("♣UnluckyCh♣ ");
				break;
			case 21:
				tag = crypt_str("♣UnluckyC♣ ");
				break;
			case 22:
				tag = crypt_str("♣Unlucky♣ ");
				break;
			case 23:
				tag = crypt_str("♣Unluck♣ ");
				break;
			case 24:
				tag = crypt_str("♣Unluc♣ ");
				break;
			case 25:
				tag = crypt_str("♣Unlu♣ ");
				break;
			case 26:
				tag = crypt_str("♣Unl♣ ");
				break;
			case 27:
				tag = crypt_str("♣Un♣ ");
				break;
			case 28:
				tag = crypt_str("♣U♣ ");
				break;
			case 29:
				tag = crypt_str("♣♣ ");
				break;
			case 30:
				tag = crypt_str("♣ ");
				break;
			case 31:
				tag = crypt_str(" ");
				break;
			}

			apply(tag);
			time = main_time;
		}

		removed = false;
	}
}
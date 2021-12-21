#pragma once

#include "..\..\includes.hpp"

class spammers : public  singleton< spammers > {
public:
	void clan_tag();
	void clan_tag_pastesense();
	void clan_tag_unlucky();
};
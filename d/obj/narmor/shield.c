//金色装备：有1条随机属性的装备
//蓝色装备：有3到10条随机属性的装备，属性越多，出现的概率越低		
//橙色装备：有2条随机属性的装备
//红色装备：有3条固定属性的装备，第四条属性随机，并有可能额外出现1到3条随机属性
//紫色装备：有4条固定属性的装备，第五条属性随机，并有可能额外出现1到3条随机属性				 
#include <ansi.h>
#include <armor.h>
inherit __DIR__"newcloth.c";
#include "shield.h"

mapping a_names1(){ return names1;}
mapping a_names2(){ return names2;}

void create()
{
	set_name("防具◆盾牌",({"shiled"}));
	set("armor_type", TYPE_SHIELD);
	setup();
}
/*
mapping a_title()
{
	return ([
	"辛环"   : ({"hammer","ad_hammer",}),
	"吕不韦" : ({"intelligence","courage","spells_damage","combat_def",}),
	"女英"   : ({"personality","intelligence","receive_curing_kee","receive_curing_sen",}),
	"关云长" : ({"ad_blade","combat_damage","combat_succ",}),
	"太史慈" : ({"ad_mace","combat_damage","combat_succ",}),
	"程咬金" : ({"ad_sanban-axe","combat_damage","karma",}),
	"李艮"   : ({"ad_fork","ad_fengbo-cha","ad_dragonforce"}),
	"黑无常" : ({"whip","ad_hellfire-whip",}),
	]);
}	
*/
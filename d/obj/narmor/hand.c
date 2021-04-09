//金色装备：有1条随机属性的装备
//蓝色装备：有3到10条随机属性的装备，属性越多，出现的概率越低		
//橙色装备：有2条随机属性的装备
//红色装备：有3条固定属性的装备，第四条属性随机，并有可能额外出现1到3条随机属性
//紫色装备：有4条固定属性的装备，第五条属性随机，并有可能额外出现1到3条随机属性				 
#include <ansi.h>
#include <armor.h>
inherit __DIR__"newcloth.c";
#include "hand.h"

void create()
{
	set_name("防具◆护手",({"hand"}));
	set("armor_type", TYPE_HANDS);
	setup();
}

mapping a_names1(){ return names1;}
mapping a_names2(){ return names2;}
/*
mapping a_title()
{
	return ([
	"邓九公" : ({"blade","ad_blade",}),
	"甄洛"   : ({"personality","intelligence","spells_succ","spells_dodge",}),
	"柳下惠" : ({"personality","intelligence","combat_parry","force_recover",}),
	"敖广"   : ({"unarmed","ad_unarmed","ad_dragonfight"}),
	"曹国舅" : ({"hammer","ad_hammer","ad_baguazhen",}),
	"韩湘子" : ({"ad_sword","sword","ad_xiaofeng-sword"}),
	"吕洞宾" : ({"ad_sword","ad_sanqing-jian",}),
	"孔雀公主":({"personality","ad_bainiao-jian","ad_bingpo-blade","ad_cuixin-zhang",}),
	]);
}
*/	
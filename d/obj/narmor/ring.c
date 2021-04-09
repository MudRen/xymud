//金色装备：有1条随机属性的装备
//蓝色装备：有3到10条随机属性的装备，属性越多，出现的概率越低		
//橙色装备：有2条随机属性的装备
//红色装备：有3条固定属性的装备，第四条属性随机，并有可能额外出现1到3条随机属性
//紫色装备：有4条固定属性的装备，第五条属性随机，并有可能额外出现1到3条随机属性				 
#include <ansi.h>
#include <armor.h>
inherit __DIR__"newcloth.c";
#include "ring.h"

mapping a_names1(){ return names1;}
mapping a_names2(){ return names2;}

void create()
{
	set_name("防具◆戒指",({"ring"}));
	set("armor_type", TYPE_FINGER);
	setup();
}
/*
mapping a_title()
{
	return ([
	"邓婵玉" : ({"throwing","personality",}),
	"班婕妤" : ({"personality","intelligence","spells_def","spells_damage",}),
	"韩信"   : ({"strength","intelligence","attack","defense",}),
	"东方朔" : ({"composure","intelligence","spells_succ","defense",}),
	"甄洛"   : ({"personality","intelligence","spells_succ","spells_dodge",}),
	"罗敷"   : ({"personality","intelligence","spells_dodge","combat_succ",}),
	"飞燕"   : ({"personality","intelligence","force_recover","fofce_refresh",}),
	"妲己"   : ({"personality","intelligence","fofce_refresh","receive_heal_kee",}),
	"湘君"   : ({"personality","intelligence","receive_heal_kee","receive_heal_sen",}),
	"娥皇"   : ({"personality","intelligence","receive_heal_sen","receive_curing_kee",}),
	"女英"   : ({"personality","intelligence","receive_curing_kee","receive_curing_sen",}),
	"虞姬"   : ({"personality","intelligence","receive_curing_sen","receive_exercise",}),
	"西施"   : ({"personality","intelligence","receive_meditate","receive_exercise"}),	
	"韩湘子" : ({"ad_sword","sword","ad_xiaofeng-sword"}),
	"吕洞宾" : ({"ad_sword","ad_sanqing-jian",}),
	"何仙姑" : ({"sword","ad_sanqing-jian","personality"}),
	"嫦娥"   : ({"personality","ad_moondance","ad_snowsword"}),
	"凝眸仙子":({"personality","ad_zongheng-sword","ad_siji-zhang"}),
	"痴梦仙子":({"ad_whip","ad_jueqingbian","personality",}),
	"孔雀公主":({"personality","ad_bainiao-jian","ad_bingpo-blade","ad_cuixin-zhang",}),
	]);
}	
*/
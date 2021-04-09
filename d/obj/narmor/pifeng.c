//金色装备：有1条随机属性的装备
//蓝色装备：有3到10条随机属性的装备，属性越多，出现的概率越低		
//橙色装备：有2条随机属性的装备
//红色装备：有3条固定属性的装备，第四条属性随机，并有可能额外出现1到3条随机属性
//紫色装备：有4条固定属性的装备，第五条属性随机，并有可能额外出现1到3条随机属性				 
#include <ansi.h>
#include <armor.h>
inherit __DIR__"newcloth.c";
#include "pifeng.h"

mapping a_names1(){ return names1;}
mapping a_names2(){ return names2;}

void create()
{
	set_name("防具◆披风",({"pifeng"}));
	set("armor_type", TYPE_SURCOAT);
	setup();
}
/*
mapping a_title()
{
	return ([
	"闻仲"   : ({"mace","ad_mace",}),
	"辛环"   : ({"hammer","ad_hammer",}),
	"余化"   : ({"spells","ad_spells",}),
	"黄飞虎" : ({"spear","ad_spear","wuyue-spear",}),
	"姜子牙" : ({"spells_succ","spells_dodge",}),
	"申公豹" : ({"combat_succ","combat_dodge","combat_parry",}),
	"相柳"   : ({"spells_damage","combat_damage",}),
	"昭君"   : ({"personality","intelligence","combat_succ","combat_dodge",}),
	"娥皇"   : ({"personality","intelligence","receive_heal_sen","receive_curing_kee",}),
	"项羽"   : ({"combat_damage","re_spells_damage","receive_force",}),
	"张翼德" : ({"spear","ad_spear","strength","re_combat_damage","receive_mana",}),
	"白起"   : ({"unarmed","ad_unarmed","constitution",}),
	"吕奉先" : ({"ad_spear","combat_damage","combat_succ",}),
	"张果老" : ({"hammer","ad_hammer","ad_kaishan-chui",}),
	"铁拐李" : ({"staff","ad_staff","ad_fumo-zhang",}),
	"李艮"   : ({"ad_fork","ad_fengbo-cha","ad_dragonforce"}),
	"罗成"   : ({"ad_spear","ad_bawang-qiang",}),
	"孙悟空" : ({"ad_stick","ad_qianjun-bang","re_combat_damage"}),
	"太清真人":({"ad_yujianshu","ad_tianshi-fufa","ad_sword","re_spells_damage",}),
	]);
}	
*/
//金色装备：有1条随机属性的装备
//蓝色装备：有3到10条随机属性的装备，属性越多，出现的概率越低		
//橙色装备：有2条随机属性的装备
//红色装备：有3条固定属性的装备，第四条属性随机，并有可能额外出现1到3条随机属性
//紫色装备：有4条固定属性的装备，第五条属性随机，并有可能额外出现1到3条随机属性				 
#include <ansi.h>
#include <armor.h>
inherit __DIR__"newcloth.c";
#include "kui.h"

mapping a_names1(){ return names1;}
mapping a_names2(){ return names2;}

void create()
{
	set_name("防具◆盔",({"kui"}));
	set("armor_type", TYPE_HEAD);
	setup();
}
/*
mapping a_title()
{
	return ([
	"闻仲"   : ({"mace","ad_mace",}),
	"黄飞虎" : ({"spear","ad_spear","wuyue-spear",}),
	"相柳"   : ({"spells_damage","combat_damage",}),
	"吕不韦" : ({"intelligence","courage","spells_damage","combat_def",}),
	"萧何"   : ({"intelligence","constitution","combat_def","combat_damage",}),
	"宋玉"   : ({"personality","intelligence","combat_dodge","combat_parry",}),
	"项羽"   : ({"combat_damage","re_spells_damage","receive_force",}),
	"张翼德" : ({"spear","ad_spear","strength","re_combat_damage","receive_mana",}),
	"白起"   : ({"unarmed","ad_unarmed","constitution",}),
	"吕奉先" : ({"ad_spear","combat_damage","combat_succ",}),
	"关云长" : ({"ad_blade","combat_damage","combat_succ",}),
	"太史慈" : ({"ad_mace","combat_damage","combat_succ",}),
	"程咬金" : ({"ad_sanban-axe","combat_damage","karma",}),
	"敖广"   : ({"unarmed","ad_unarmed","ad_dragonfight"}),
	"玉鼠精" : ({"blade","ad_blade","ad_kugu-blade","ad_yinfeng-zhua","personality",}),
	"张果老" : ({"hammer","ad_hammer","ad_kaishan-chui",}),
	"龟八斗" : ({"ad_hammer","hammer","ad_huntian-hammer",}),
	"罗成"   : ({"ad_spear","ad_bawang-qiang",}),
	"孙悟空" : ({"ad_stick","ad_qianjun-bang","re_combat_damage"}),
	"白无常" : ({"stick","ad_kusang-bang","ad_stick",}),
	"黑无常" : ({"whip","ad_hellfire-whip",}),
	]);
}
*/
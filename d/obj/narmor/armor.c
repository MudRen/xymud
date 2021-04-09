//金色装备：有1条随机属性的装备
//蓝色装备：有3到10条随机属性的装备，属性越多，出现的概率越低		
//橙色装备：有2条随机属性的装备
//红色装备：有3条固定属性的装备，第四条属性随机，并有可能额外出现1到3条随机属性
//紫色装备：有4条固定属性的装备，第五条属性随机，并有可能额外出现1到3条随机属性				 
#include <ansi.h>
#include <armor.h>
inherit __DIR__"newcloth.c";
#include "armors.h"

mapping a_names1(){return names1;}
mapping a_names2(){return names2;}

void create()
{
	set_name("防具◆甲",({"armor"}));
	set("armor_type", TYPE_ARMOR);
	set("unit","件");
	setup();
}
/*
mapping a_title()
{
	return ([
	"闻仲"   : ({"mace","ad_mace",}),
	"邓九公" : ({"blade","ad_blade",}),
	"黄飞虎" : ({"spear","ad_spear","wuyue-spear",}),
	"吕岳"   : ({"spells","ad_spells",}),
	"土行孙" : ({"dodge","ad_dodge",}),
	"相柳"   : ({"spells_damage","combat_damage",}),
	"虞姬"   : ({"personality","intelligence","receive_curing_sen","receive_exercise",}),
	"项羽"   : ({"combat_damage","re_spells_damage","receive_force",}),
	"张翼德" : ({"spear","ad_spear","strength","re_combat_damage","receive_mana",}),
	"白起"   : ({"unarmed","ad_unarmed","constitution",}),
	"吕奉先" : ({"ad_spear","combat_damage","combat_succ",}),
	"关云长" : ({"ad_blade","combat_damage","combat_succ",}),
	"太史慈" : ({"ad_mace","combat_damage","combat_succ",}),
	"程咬金" : ({"ad_sanban-axe","combat_damage","karma",}),
	"敖广"   : ({"unarmed","ad_unarmed","ad_dragonfight"}),
	"玉鼠精" : ({"blade","ad_blade","ad_kugu-blade","ad_yinfeng-zhua","personality",}),
	"铁拐李" : ({"staff","ad_staff","ad_fumo-zhang",}),
	"汉钟离" : ({"blade","ad_blade","ad_yange-blade",}),
	"曹国舅" : ({"hammer","ad_hammer","ad_baguazhen",}),
	"嫦娥"   : ({"personality","ad_moondance","ad_snowsword"}),
	"李艮"   : ({"ad_fork","ad_fengbo-cha","ad_dragonforce"}),
	"罗成"   : ({"ad_spear","ad_bawang-qiang",}),
	"孙悟空" : ({"ad_stick","ad_qianjun-bang","re_combat_damage"}),
	"白无常" : ({"stick","ad_kusang-bang","ad_stick",}),
	"黑无常" : ({"whip","ad_hellfire-whip",}),
]);
}	
*/	
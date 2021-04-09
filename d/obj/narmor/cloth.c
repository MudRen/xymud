//金色装备：有1条随机属性的装备
//蓝色装备：有3到10条随机属性的装备，属性越多，出现的概率越低		
//橙色装备：有2条随机属性的装备
//红色装备：有3条固定属性的装备，第四条属性随机，并有可能额外出现1到3条随机属性
//紫色装备：有4条固定属性的装备，第五条属性随机，并有可能额外出现1到3条随机属性				 
#include <ansi.h>
#include <armor.h>
inherit __DIR__"newcloth.c";
#include "cloth.h"

mapping a_names1(){ return names1;}
mapping a_names2(){ return names2;}

void create()
{
	set_name("防具◆袍",({"cloth"}));
	set("armor_type", TYPE_CLOTH);		
	setup();
}
/*
mapping a_title()
{
	return ([
	"余化"   : ({"spells","ad_spells",}),
	"黄飞虎" : ({"spear","ad_spear","wuyue-spear",}),
	"姜子牙" : ({"spells_succ","spells_dodge",}),
	"申公豹" : ({"combat_succ","combat_dodge","combat_parry",}),
	"相柳"   : ({"spells_damage","combat_damage",}),
	"吕不韦" : ({"intelligence","courage","spells_damage","combat_def",}),
	"东方朔" : ({"composure","intelligence","spells_succ","defense",}),
	"昭君"   : ({"personality","intelligence","combat_succ","combat_dodge",}),
	"宋玉"   : ({"personality","intelligence","combat_dodge","combat_parry",}),
	"柳下惠" : ({"personality","intelligence","combat_parry","force_recover",}),
	"湘君"   : ({"personality","intelligence","receive_heal_kee","receive_heal_sen",}),
	"西施"   : ({"personality","intelligence","receive_meditate","receive_exercise"}),	
	"白起"   : ({"unarmed","ad_unarmed","constitution",}),
	"吕奉先" : ({"ad_spear","combat_damage","combat_succ",}),
	"张果老" : ({"hammer","ad_hammer","ad_kaishan-chui",}),
	"铁拐李" : ({"staff","ad_staff","ad_fumo-zhang",}),
	"汉钟离" : ({"blade","ad_blade","ad_yange-blade",}),
	"龟八斗" : ({"ad_hammer","hammer","ad_huntian-hammer",}),
	"孙悟空" : ({"ad_stick","ad_qianjun-bang","re_combat_damage"}),
	"太清真人":({"ad_yujianshu","ad_tianshi-fufa","ad_sword","re_spells_damage",}),
	]);
}
*/
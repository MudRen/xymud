//金色装备：有1条随机属性的装备
//蓝色装备：有3到10条随机属性的装备，属性越多，出现的概率越低		
//橙色装备：有2条随机属性的装备
//红色装备：有3条固定属性的装备，第四条属性随机，并有可能额外出现1到3条随机属性
//紫色装备：有4条固定属性的装备，第五条属性随机，并有可能额外出现1到3条随机属性				 
#include <ansi.h>
#include <armor.h>
inherit __DIR__"newcloth.c";
#include "shoes.h"

mapping a_names1(){return names1;}
mapping a_names2(){return names2;}

void create()
{
	set_name("防具◆鞋",({"xie"}));
	set("armor_type", TYPE_BOOTS);
	setup();
}
/*
汉 雌亭侯 许负 女
三国 管珞 朱建平 柳无景
隋唐 韦鼎 来和  袁天罡 龙复本 夏荣 丁重 张憬藏 刘思礼 袁客师 
*/
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("龙复本", ({"long fuben", "long" ,"fuben"}));
        set("gender", "男性" );
        set_level(50);
        set("age", 25);
        set("class","taoist");
        set("long", "云游四方，他嘴里说的每一个卦辞都立判人生死。\n");

        set("attitude", "peaceful");
        set_skill("unarmed",500);
        set_skill("dodge",500);
        set_skill("force",500);
        set_skill("parry",500);
        set_skill("sword",500);
        set_skill("literate",500);
	set_skill("scratmancy",500); 
        set_skill("spells", 150);
        set_skill("five-avoid",500);
        set_skill("yinyang-zhang",500);
        set_skill("bolomiduo",500);
        set_skill("wuzheng-force",500);
        set_skill("zhanbu",500);
        set_skill("blade",500);
        set_skill("pomo-blade",500);
        
        set("mana_factor", 300);
        create_family2("五庄观","相士",4,HIM"铁口神相"NOR);
        setup();
        carry_object("/d/obj/weapon/blade/poshidao")->wield();
        carry_object(0,"cloth",random(3))->wear();
        carry_object(0,"shoes",random(3))->wear();
        carry_object(0,"pifeng",random(3))->wear();
	powerup(1,1);
}

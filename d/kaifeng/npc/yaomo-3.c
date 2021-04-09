//snowtu 2009
#include <ansi.h>
#include <combat.h>
inherit __DIR__"yaomo.c";

void setskills()
{
        set_skill("zhenyuan-force", 120);
        set_skill("taiyi", 120);
        set_skill("baguazhen", 120);
        set_skill("sanqing-jian", 120);
        set_skill("sword", 120);
        set_skill("wuxing-quan", 120);
        map_skill("spells", "taiyi");
        map_skill("unarmed", "wuxing-quan");
        map_skill("force", "zhenyuan-force");
        map_skill("sword", "sanqing-jian");
        map_skill("parry", "sanqing-jian");
        map_skill("dodge", "baguazhen");
        set("family/family_name","五庄观");
}

void special_att(object who)
{
        object weapon;
        object me = this_object();
        reset_eval_cost();        
        if( !living(me) || !who
         || !me->is_fighting(who) )
                return;
        command("wield sword");
        weapon = me->query_temp("weapon");
        if( !weapon )
                weapon = carry_object("/d/city/obj/sword")->wield();
        if( random(20)==8 )
                QUEST_D->randomPfm(me);
}


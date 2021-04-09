//snowtu 2009
#include <ansi.h>
#include <combat.h>
inherit __DIR__"yaomo.c";

void setskills()
{
        set_skill("huntian-hammer", 120);
        set_skill("hammer", 120);
        set_skill("fork", 120);
        set_skill("seashentong", 120);
        set_skill("dragonfight", 120);
        set_skill("dragonforce", 120);
        set_skill("fengbo-cha", 120);
        set_skill("dragonstep", 120);
        map_skill("hammer", "huntian-hammer");
        map_skill("spells", "seashentong");
        map_skill("unarmed", "dragonfight");
        map_skill("force", "dragonforce");
        map_skill("fork", "fengbo-cha");
        map_skill("parry", "fengbo-cha");
        map_skill("dodge", "dragonstep");
        set("family/family_name","东海龙宫");
}

void special_att(object who)
{
        object weapon;
        object me = this_object();
        reset_eval_cost();        
        if( !living(me) || !who
         || !me->is_fighting(who) )
                return;
        if( random(20)==17 )
        {                
                command("unwield fork");
                command("wield fork");
                weapon = me->query_temp("weapon");
                if( !weapon )
                        weapon = carry_object("/d/city/obj/fork")->wield();
                command("perform fengbo");
        }
        command("unwield fork");
        if( random(20)==17 )
                QUEST_D->randomPfm(me);
}

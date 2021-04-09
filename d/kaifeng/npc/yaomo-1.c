//snowtu 2009
#include <ansi.h>
#include <combat.h>
inherit __DIR__"yaomo.c";

void setskills()
{
        set_skill("blade", 120);
        set_skill("sword", 120);
        set_skill("yinfeng-zhua", 120);
        set_skill("yaofa", 120);
        set_skill("qixiu-jian", 120);
        set_skill("lingfu-steps", 120);
        set_skill("kugu-blade", 120);
        set_skill("huntian-qigong", 120);
        map_skill("force", "huntian-qigong");
        map_skill("spells", "yaofa");
        map_skill("unarmed", "yinfeng-zhua");
        map_skill("sword", "qixiu-jian");
        map_skill("parry", "kugu-blade");
        map_skill("blade", "kugu-blade");
        map_skill("dodge", "lingfu-steps");
        set("family/family_name","陷空山无底洞");       
}

        
void special_att(object who)
{
        object weapon;
        object me = this_object();
        reset_eval_cost();        
        if( !living(me) || !who
         || !me->is_fighting(who) )
                return;
        command("unwield blade");
        command("unwield sword");
        command("wield sword");
        weapon = me->query_temp("weapon");
        if( !weapon )
                weapon = carry_object("/d/city/obj/sword")->wield();
        if( random(10)==8 )
                QUEST_D->randomPfm(me);
        if( random(20)==8 )
        {                
                command("unwield sword");
                command("wield blade");
                weapon = me->query_temp("weapon");
                if( !weapon )
                        weapon = carry_object("/d/city/obj/blade")->wield();
                if( random(10)==8 )
                        QUEST_D->randomPfm(me);
        }
}

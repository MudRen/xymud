// sgzl
// Improved by lzh 2009.06.11
// /d/dntg/hgs/npc/mowang.c 大闹天宫第一关Boss
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("混世魔王", ({ "hunshi mowang", "mowang"}) );
        set("gender", "男性" );
        set("long",
                "只见这魔王：\n
　　头戴乌金盔，映日光明；身挂皂罗袍，迎风飘荡。
    下穿着黑铁甲，紧勒皮条；足踏着花褶靴，雄如上将。
    腰广十围，身高三丈，手执一口刀，锋刃多明亮。
    称为混世魔，磊落凶模样。\n");
        set("age", 30);
        set("str", 30);
        set("per", 30);
        set("int", 30);
        set("attitude", "killer");

        set("family/family_name", "陷空山无底洞"); 
        set("combat_exp", 20000000);
        set("daoxing", 30000000);
        set_skill("force",  random(50)+250); 
        set_skill("spells", random(50)+250); 
        set_skill("unarmed", random(50)+250); 
        set_skill("blade",  random(50)+250); 
        set_skill("dodge",  random(50)+250); 
        set_skill("parry",  random(50)+250); 
        set_skill("xiaoyaoyou",  random(50)+250);       
        set_skill("yaofa", random(50)+250); 
        set_skill("ningxie-force", random(50)+250); 
        set_skill("kugu-blade",  random(50)+250); 
        set_skill("jinwu-blade",  random(50)+250); 
        set_skill("dragonfight",  random(50)+250); 


        map_skill("force", "ningxie-force");
        map_skill("spells", "yaofa");
        map_skill("blade", "jinwu-blade");
        map_skill("parry", "jinwu-blade");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("unarmed", "dragonfight");

        set("max_kee", 10000);
        set("max_sen", 12000);
        set("max_force", 20000);
        set("max_mana", random(8000)+15000);
        set("force_factor", 50);

        setup();

        carry_object("/d/obj/armor/tongjia.c")->wear();
        carry_object("/d/obj/cloth/shoupiqun")->wear();
        carry_object("/d/obj/weapon/blade/yanblade.c")->wield();
        carry_object("/d/dntg/hgs/obj/hunshi-ring")->wear();    
}

void init()
{
        object ob=this_player();

        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
}

void greeting(object ob)
{
        object me=this_object();
        if( !ob || !present(ob,environment()) )
                return; 
        message_vision("$N喝道：这地盘老子占了，来找死嘛！\n",me);
        command("kill " + ob->query("id"));
}


int accept_fight (object ob)
{
        if( !ob || !present(ob,environment()) )
                return 1;
        ob->apply_condition ("killer",100);
        kill_ob (ob);
        return 1;
}

void kill_ob (object ob)
{
        object me = this_object();
        if( !ob || !present(ob,environment()) )
                return;
        set_temp("no_return",1);
        set_temp("my_killer",ob);
        call_out ("hurting",random(5)+5,me,ob);
        ::kill_ob(ob);
}

void hurting (object me, object ob)
{
        string *msgs = ({
                HIC"$N"HIC"手中的宝刀一阵狂舞，劈头盖脸的朝着$n"HIC"招呼！\n"NOR,
                HIY"$N"HIY"手腕陡然猛颤，无数刀气从刀锋中飞了出来！\n"NOR,
        });
        string *strs = ({
                HIR"$N"HIR"躲避不及，身上顿时被砍出十七八道血痕！\n"NOR,
                HIM"$N"HIM"身中数刀，痛苦不堪，神情逐渐委顿了下来……！\n"NOR,
  });
        int damage,busy;

        remove_call_out("hurting");
        
        if( !me )       
                return;
        if( !ob || !present(ob,environment()) || !me->is_fighting(ob) )
        {
                powerup(1);
                return;
        }
        command("wield blade");
        if( !query_temp("weapon") )
                carry_object("/d/obj/weapon/blade/yanblade.c")->wield();
        busy = (int)this_object()->query_busy();
        if( busy )
        {
                damage = ob->query("max_kee")/(10+random(10));
                damage-= random(ob->query_temp("apply/armor"));
                if( damage>0 )
                {               
                        message_vision ("\n"+msgs[random(sizeof(msgs))],me,ob);
                        message_vision ("\n"+strs[random(sizeof(strs))],ob);
                        ob->receive_wound("kee",damage);
                        ob->receive_damage("kee",damage);
                        ob->set_temp("death_msg","被混世魔王一刀劈为两段！\n");
                }
        }
        else
        {
                if( random(2) )
                {
                        map_skill("blade", "kugu-blade");
                        command("perform pozhan");
                }
                map_skill("blade", "jinwu-blade");              
                if( living(this_object()) )
                        QUEST_D->randomPfm(this_object());
        }
        call_out ("hurting",random(5)+3,me,ob);  
}


void heart_beat() 
{ 
        object me = this_object(); 

        if( !environment() ) 
                return;
        if( query("force")<500 )
        {
                if( query("kee")<=0 || query("eff_kee")<=0 )
                {
                        die();
                        return;
                }
                if( query("sen")<0 || query("eff_sen")<=0 )
                {
                        unconcious();
                        return;
                }
        }

        me->clear_condition();

        if ( query("eff_kee") < query("max_kee") ) 
                QUEST_D->addEffKee(me,random(5)); 
        if ( query("kee") < query("eff_kee") ) 
                QUEST_D->addKee(me); 
        if ( query("sen") < query("eff_sen") ) 
                QUEST_D->addSen(me,random(5)); 
        if ( query("eff_sen") < query("max_sen") ) 
                QUEST_D->addEffSen(me); 
        ::heart_beat();
}

void die()
{
        object ob = query_temp("my_killer");
        object me = this_object();
        object ma;
          object panzi;

        if(ob && present(ob,environment()) )
        {
                message_vision ("\n$N惨叫一声，被砍为两段。\n",me);
                ma = new (__DIR__"ma");
                message_vision ("\n猴子头领马元帅领着几只猴子跑了过来，看到$N被斩，高兴的跳了起来。\n",me);
                if(ob->query("dntg/huaguo")!="done" && userp(ob))  
                {
                        ma->announce_success (ob);
                        panzi = new ("/d/dntg/hgs/obj/shipan");
                        panzi->move(ob);
                }
                message_vision ("\n马元帅带着众猴子七手八脚的把$N的尸体拖了出去。\n",me);
                destruct (ma);
        }
        destruct(me);
}

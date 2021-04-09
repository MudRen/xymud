//Cracked by Roath
// created by snowcat on 12/9/1997
//snowtu 2009
#include <ansi.h>
#include <combat.h>
inherit NPC;

#ifndef SDS_D
#define SDS_D "/d/newguai/npc/sdsd.c"
#endif

object ye = 0;

void do_kill(object obs);

string *names1 = ({
        "獭","鹿","獾","狗","猪","猴","狒","蟒",
});

string *names2 = ({
        "头","尾","脚","爪","嘴","牙",
});

string *names3 = ({
        "虎","狮","豹","熊","罴","狼","狈","豺",
});

int eff_dx;
int already_setup=0;
int random_action();
void set_data();
void setskills(){ return; }

void create()
{
        object who,*usr;
        string str;
        
        str = names1[random(sizeof(names1))]+names2[random(sizeof(names2))]+names3[random(sizeof(names3))];
        set_name(str, ({"yao mo", "yao", "mo"}));
        set("gender", "男性");
        set("attitude", "aggressive");
        set("chat_chance", 10);
        set("env/brief_message",2);
        set("env/wimpy",30);        
        set("chat_msg", ({
                (: random_action :)
        }));
        set_skill("dodge", 120);
        set_skill("force", 120);
        set_skill("spells", 120);
        set_skill("parry", 120);
        set_skill("literate", 150);     
        set_skill("unarmed", 120);
        setskills();
        setup();
        carry_object("/d/obj/cloth/shoupiqun")->wear();
        add_temp("apply/damage",10);
        add_temp("apply/attack",10);
        add_temp("apply/armor",100);
        already_setup=0;
        usr = users();
        who = usr[random(sizeof(usr))];
        if( who && living(who) && !wizardp(who) && visible(who) )
        {
            set_temp("unit",who->query_temp("unit"));
            set_temp("is_character",who->query_temp("is_character"));
            set_temp("gender",who->query_temp("gender"));
            set_temp("age",who->query_temp("age"));
            set_temp("race",who->query_temp("race"));
            set_temp("family",who->query_temp("family"));
                set_temp("apply/name",({who->name()}));
                set_temp("apply/id",who->parse_command_id_list());
                set_temp("apply/short", ({who->short()}));
                set_temp("apply/long", ({who->long()}));
        }
}

void init()
{
        if(!already_setup)
                set_data();
        if(this_player()) 
                do_kill(this_player());
}

void set_data()
{
        string long,*skills;
        int i,k,m;
        int j, dx, year;
        mapping skill;
        object env=environment(this_object());

        if(!env) return;
        
        year=env->query_year();
        if(!year) 
                return;
  
        already_setup=1;
        reset_eval_cost();

        k=year/2;
        m=11*year/10;
        i=k+random((m-k)/10+1)*10;
        if(i>20000) i=20000;
        set("age", i*2);
        
        dx = year/10*year*year;
        set("combat_exp", dx);
        set("daoxing", dx);
        set("per", 10+random(30));

        skill = query_skills();
        skills = keys(skill);
        for(i=0;i<sizeof(skills);i++)
                set_skill(skills[i],year+random(year/5));      

        set("force_factor",year/3);
        set("mana_factor",year/2);

        set("max_sen",year*10);
        set("max_kee",year*10);
        set("max_force",query_skill("force")*10);
        set("max_mana",query_skill("spells")*10);

        set("kee",query("max_kee"));
        set("eff_kee",query("max_kee"));
        set("sen",query("max_sen"));
        set("eff_sen",query("max_sen"));
        set("mana",query("max_mana")*2);
        set("force",query("max_force")*2);
        
  // mon 9/25/98
        j=(random(2)==0)?1:-1;
        eff_dx=dx*j;
        set("eff_dx",eff_dx);
        set("nkgain",600);
        long="一头"+name()+"，修练了有"+chinese_number((dx/1000/10)*10)+"多年道行。它";
        if(j==1) 
                set("long",long+"通体透出一丝仙气。\n");
        else    set("long",long+"混身上下妖气逼人。\n");
        set("env/wimpy",30);
}

void do_kill(object obs)
{
        int exp;
        if(!obs || (!userp(obs) && !obs->is_rzr() ) )
                return;
        kill_ob(obs);
        if(!random(5))
                set_follow(obs);
        else if(!random(5))
                set_follow(0);
}

      
void kill_ob(object who)
{
        if( !environment() )
                return;
        if( !who || !present(who,environment()) )
                return;
        ::kill_ob(who);
}               

int random_action()
{
        object env = environment(this_object());
        object *obs;
        int i;

        if( !is_fighting() 
         && living(this_object()) 
         && env ) 
        {
                random_move();
                env = environment(this_object()); // notice: new env
                obs = all_inventory(env);
                i = sizeof(obs);
                while (i--) 
                        do_kill(obs[i]);
        }
        return 0;
}

void die()
{
        object killer,me = this_object();
        
        ye = environment()->query("master");
        if( !ye )
        {
                ::die();
                return;
        }
        message_vision(HIB"\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n"NOR,this_object());
        me->clear_condition();
        me->remove_all_killer();

        killer = query_temp("last_damage_from");
        if( killer && present(killer,environment())
         && environment()->is_ymdh()
         && killer->query_temp("ymdh/entered") )
                ye->reward_ob(killer,name());  
        destruct(me);   
}

int is_ymdh(){ return 1;}

varargs int receive_wound(string type, int damage, object who,string attack_type)
{
        if( !who || who==this_object() )
                damage  = 0;
        if( damage>800 )
                damage = 800;
        if( damage<1 ) 
                damage = 1;
        return  ::receive_wound(type,damage,who,attack_type);
}

varargs int receive_damage(string type, int damage, object who,string attack_type)
{
        if( !who || who==this_object() )
                damage  = 0;
        if( damage>1500 )
                damage = 1500;
        if( damage<1 ) 
                damage = 1;
        return  ::receive_damage(type,damage,who,attack_type);
}



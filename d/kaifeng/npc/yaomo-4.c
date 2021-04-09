//snowtu 2009
#include <ansi.h>
#include <combat.h>
inherit NPC;

void do_kill(object obs);

int eff_dx;
int already_setup=0;
int random_action();
void set_data();

void setskills()
{
        set_skill("huomoforce", 120);
        set_skill("pingtian-dafa", 120);
        set_skill("moshenbu", 120);
        set_skill("wuyue-spear", 120);
        set_skill("spear", 120);
        set_skill("moyun-shou", 120);
        map_skill("spells", "pingtian-dafa");
        map_skill("unarmed", "moyun-shou");
        map_skill("force", "huomoforce");
        map_skill("spear", "wuyue-spear");
        map_skill("parry", "wuyue-spear");
        map_skill("dodge", "moshenbu");
        set("family/family_name","火云洞");
}

void create()
{
        object who,*usr;
        mapping name = NAME_D->random_name("yaoguai");
        set_name(name["name"],name["id"]);
        set("gender", "男性");
        set("attitude", "aggressive");
        set("chat_chance", 10);
        set("env/brief_message",2);
        set("env/wimpy",40);        
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
        carry_object("/d/obj/armor/jinjia")->wear();
        already_setup=0;
        add_temp("apply/armor",100);
        add_temp("apply/damage",20);
        usr = users();
        who = usr[random(sizeof(usr))];
        if( who && living(who) )
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

        k=year/2;
        m=11*year/10;
        i=k+random((m-k)/10+1)*10;
        if(i>20000) i=20000;
        set("age", i*2);
        
        year+= 100;
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
        object weapon,env = environment();
        object *obs;
        int i;

        if( !env )
                return 0;
        if( !living(this_object()) )
                return 0;               
        if( query("force")>500 )
        {
                if( query("eff_kee")<query("max_kee") )
                        QUEST_D->addEffKee(this_object());
                if( query("eff_sen")<query("max_sen") )         
                        QUEST_D->addEffSen(this_object());
                if( query("kee")<query("eff_kee") )
                        QUEST_D->addKee(this_object());
                if( query("sen")<query("eff_sen") )             
                        QUEST_D->addSen(this_object());
        }       
        if( !is_fighting() )
                random_move();
        else if( query("force")>200 )   
        {
                command("wield spear");
                weapon = query_temp("weapon");
                if( !weapon || weapon->query("skill_type")!="spear" )
                {
                        if( weapon )
                        {
                                weapon->unequip();
                                destruct(weapon);
                                reset_action();
                        }
                        add_temp("apply/karma",3000);
                        carry_object(0,"spear",1)->wield();
						add_temp("apply/karma",-3000);
                }
                switch(random(5))
                {
                        case 0 :
                        case 4 : 
                                QUEST_D->randomPfm(this_object());break;
                        default:                                
                                QUEST_D->randomExert(this_object());break;
                }
        }
        return 0;
}

void die()
{
        object ym,box,killer,me = this_object();
        string str, msg;
        int reward;

        me->clear_condition();
        me->remove_all_killer();

        ym = present("yao mo",environment());
        if( ym && ym->is_ymdh() )
        {
                QUEST_D->powerup(me);
                message_vision(HIW"\n\n$N"HIW"战罢多时跳出圈外，大喝一声，小的们还不给我上！\n\n"NOR,me);
                random_move();
                return;
        }
        message_vision(HIY"\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n"NOR,this_object());
        killer = query_temp("last_damage_from");
        if( killer && present(killer,environment())
         && environment()->is_ymdh()
         && killer->query_temp("ymdh/entered") )
        {        
                reward = 5000;
                reward = reward/4+random(reward/2);
				str = chinese_number(reward)+"点潜能";
				tell_object(killer,"\n你得到了"+str+"！\n");
                killer->add("potential",reward);
                str = sprintf("%s打死了%s，得到了%s",killer->name(1),name(),str);
                str+="。";
                killer->add_temp("ymdh/yaomokilled",1);
                __DIR__"ye.c"->announce(str);
        }
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
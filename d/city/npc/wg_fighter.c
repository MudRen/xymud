//武馆密室陪练NPC
#include <ansi.h>
#include <combat.h>
inherit NPC;

int ttype = 1;
int set_skills(object);
void endfight();

void create() 
{
        string tmp;     
        mapping name = NAME_D->random_name("male");
        set_name(name["name"],name["id"]);
        tmp = sprintf("%c%c",name()[0],name()[1]);
        set("long",tmp+"家儿郎，如今在长安武馆勤练武艺。\n");     
        set("gender","男性");
        set("age",16+random(15));
        set("per",random(40));
        set("str",30+random(10));
        set("cor",40);
        set("cps",30);
        set("max_sen",1000);
        set("sen",1000);
        set("max_kee",2000);
        set("kee",2000);
        set("max_mana",500);
        set("combat_exp", 300);
        set("daoxing",300);
        set_skill("unarmed", 10);
        set_skill("changquan", 10);
        map_skill("unarmed", "changquan");
        set_skill("dodge", 20);
        set_skill("literate", 20);
        set_skill("force", 20);
        set_skill("lengquan-force", 20);
        set_skill("parry", 20);
        set_skill("spells", 20);
        set_skill("baguazhou", 20);
        set_skill("yanxing-steps", 20);
        map_skill("force", "lengquan-force");
        map_skill("spells", "baguazhou");
        map_skill("dodge", "yanxing-steps");  
        set("chat_chance_combat", 4);
        set("chat_msg_combat", ({
                (: endfight :),
        }));
        setup();
        carry_object("/d/city/npc/obj/spear")->wield();
}

void endfight() 
{
        message_vision(HIW"\n$N"HIW"说道：「不打了，不打了，我投降。」\n\n"NOR,this_object());
        this_object()->remove_all_killer();
        all_inventory(environment())->remove_killer(this_object());
        if( random(2) ) 
        {
                command("say 今天陪你练了这么久了，没有功劳也有苦劳，你得给点好处吧？\n");
                delete("fight_job");
		this_object()->start_busy(1);       	
        } 
        else    command("say 停！停！停！让俺休息一下。");
}

void kill_ob(object who) 
{
        int kill; //1==非owner 2==need give 3==time 4==base 5==specl
        if( !who )      return;
        if( who!=query("owner") )
                kill = 1;
        else if( !query("fight_job") )
                kill = 2;
        else if( time()<who->query_temp("fight_job_lost")+8+random(6) ) 
                kill = 3;
        else    kill = 4;
        switch(kill)
        {
                case 1 : say(CYN+query("name")+CYN"说道：范老爷子可没让我和你打。\n"NOR);
                         break;
                case 2 : say(CYN+query("name")+CYN"说道：今天陪你练了这么久了，没有功劳也有苦劳，你得给点好处吧？\n"NOR);
                         break;
                case 3 : say(CYN+query("name")+CYN"说道：你体力不支，还是休息片刻。。。。\n"NOR);
                         break;
                default:
                        if( set_skills(who) )
                        { 
                                say(CYN+query("name")+CYN"说道：英雄，手下留情啊~~~\n"NOR);
                                ::kill_ob(who);
                                return;
                        }
                        say(CYN+query("name")+CYN"说道：还是让我休息片刻。。。。\n"NOR);
                        break;
        }
        who->remove_killer(this_object());
        this_object()->remove_killer(who);
        return;
}

int set_skills(object me) 
{
        mapping skill=me->query_skills();
        int max_value=10;
        string *skillnames;

        if( !me || !skill || !mapp(skill) )
                return 0;
        skillnames=keys(skill);
        for (int i=0;i<sizeof(skillnames);i++) 
        {
                if( skill[skillnames[i]]>max_value )
                        max_value=skill[skillnames[i]];
        }
        if(query("max_force")<me->query("max_force")) 
                set("max_force",me->query("max_force")*(10+random(3))/10);
        if(query("daoxing")<me->query("daoxing")) 
                set("daoxing",me->query("daoxing")/2*3);
        if(query("comat_exp")<me->query("combat_exp")) 
                set("combat_exp",me->query("combat_exp")/2*3);
        set("force",query("max_force")*2);
        set("mana",query("max_mana")*2);
        if( query_skill("unarmed")<max_value ) 
        {    
                max_value=max_value*(10+random(3))/10;
                set_skill("unarmed", 10);
                set_skill("changquan", max_value);
                map_skill("unarmed", "changquan");
                set_skill("dodge", max_value);
                set_skill("literate", max_value);
                set_skill("force", max_value);
                set_skill("lengquan-force", max_value);
                set_skill("parry", max_value);
                set_skill("bawang-qiang", max_value);
                set_skill("spear", max_value);
                map_skill("parry", "bawang-qiang");
                map_skill("spear", "bawang-qiang");
                set_skill("spells", max_value);
                set_skill("baguazhou", max_value);
                set_skill("yanxing-steps", max_value);
                map_skill("force", "lengquan-force");
                map_skill("spells", "baguazhou");
                map_skill("dodge", "yanxing-steps");  
                set("force_factor",query_skill("force")/2); 
        }
        return 1;
}

varargs int receive_wound(string type, int damage, object who) 
{
        damage = 0;
        return ::receive_damage(type,damage,who);
}

varargs int receive_damage(string type, int damage, object who) 
{
	object weapon;
        int lvl;
        string skill,attack_skill;

        if( !who || who==this_object() || !query("REWORDS") )
        {
                damage = 0;
                return ::receive_damage(type,damage,who);
        }
        ttype = who->query_temp("wg_fighter");        
        if( ttype<5 )
        {
		say(CYN+query("name")+CYN"说道：今天陪你练了这么久了，没有功劳也有苦劳，你得给点好处吧？\n"NOR);        	
	        who->remove_killer(this_object());
        	this_object()->remove_killer(who);
                damage = 0;
		this_object()->start_busy(1);
		delete("REWORDS");
        	delete("RELVL");       	
                return ::receive_damage(type,damage,who);        	
        }
	
	skill = query("REWORDS");
        if( !skill || type!="kee" || who->query_skill(skill,1)<=100 )
	{
		say(query("name")+"说道：英雄，你的武器用的不对。\n");
        	delete("REWORDS");
        	delete("RELVL");		
		return ::receive_damage(type,damage,who); 
	}              

	weapon = who->query_temp("weapon");
        //挑战武器Move效果激活                  
        if( weapon && who->query_temp("weapon_apply") && !weapon->query("fly") && weapon->query("weapon_level")>=100 )   
        {
                weapon->add_temp("fly_apply",1+random(5));
                if( weapon->query_temp("fly_apply")>=50 )  
                {
                        weapon->set("fly",1);
                        tell_object(who,HIW"\n\n你的"+weapon->query("name")+HIW"得到了风神的庇佑！\n\n"NOR);
                        weapon->unequip();
                        who->reset_action();
                        weapon->save();
                        message_vision(HIW"\n$N"HIW"将"+weapon->query("name")+HIW"卸除下来，细心观察，只见其上疾风缠绕，甚是好看。\n\n"NOR,who);
                        who->remove_killer(this_object());
                        this_object()->remove_killer(who);
                        return 1;
                }
                else    tell_object(who,HIW"\n"+weapon->query("name")+HIW"上疾风缠绕，彷佛轻灵了不少。。。\n"NOR);
        }
	
        if( time()>=query("fight_time/start")+query("fight_time/time") )
        {
                command("say 今天陪你练了这么久了，没有功劳也有苦劳，你得给点好处吧？\n");
                delete("fight_job");
	        who->remove_killer(this_object());
        	this_object()->remove_killer(who);
                damage = 0; 
                this_object()->start_busy(1);   
        	delete("REWORDS");
        	delete("RELVL");
                return ::receive_damage(type,damage,who);
        } 
	
	lvl = query("RELVL");	
	if( lvl*lvl/10*lvl/10>=who->query("combat_exp")/10 )
	{
                command("say 你的武学修为太低，还是先去修炼修炼再来吧。\n");
                delete("fight_job");
	        who->remove_killer(this_object());
        	this_object()->remove_killer(who);
                damage = 0; 
                this_object()->start_busy(1);       	
        	delete("REWORDS");
        	delete("RELVL");                
                return ::receive_damage(type,damage,who);
	}
	if( ttype>=9 )
	{
		if( SKILL_D(skill)->valid_learn(who) )
			who->improve_skill(skill,(lvl/3+lvl/3)*(1+random(3)),(random(50)+random(50)));	
	}
	else
	{
		if( SKILL_D(skill)->valid_learn(who)        //必须能学习之特殊技能
          	 && SKILL_D(skill)->practice_skill(who) )   //必须能练习之特殊技能
			who->improve_skill(skill,lvl/3+lvl/3*(1+random(4)),random(20));
        }
        delete_temp("no_move");
        damage = 1+random(10);
        return ::receive_damage(type,damage,who);
}

int accept_object(object who,object obj)
{
	mapping skills;
	string skill;
	object weapon;
	int value;
        if( who->query("combat_exp")>1300000000
         || who->query("daoxing")>1300000000 )
        {
                say(query("name")+"说道：你太厉害了。。。。\n");
                return 0;
        }       
        value=obj->value();
        if( !value || who!=query("owner") || !obj->query("money_id") )
        	return 0;
        if( value<1000 )
        	return 0;

	weapon = who->query_temp("weapon");
	if( !weapon )
		skill = "unarmed";
	else	skill = weapon->query("skill_type");
	skills = who->query_skills();
	if( !skills || !mapp(skills) )
	{
		say(query("name")+"一哈腰，说道：您老这"+to_chinese(skill)+"的修为恐怕不经小的一招。\n");	 		
        	return 0;
	}
        if( undefinedp(skills[skill]) || skills[skill]<=100 )
	{
		say(query("name")+"一哈腰，说道：您老这"+to_chinese(skill)+"的修为恐怕不经小的一招。\n");	 		
        	return 0;
	}

	value = value/10000+4;
	if( value<9 )
		skill = who->query_skill_mapped(skill);
	if( !skill )
	{
		say(query("name")+"一哈腰，说道：您老拿错武器了吧。\n");	 		
        	return 0;
	}	

        who->set_temp("wg_fighter",value);
        set("REWORDS",skill);
        set("RELVL",skills[skill]);
	say(query("name")+"一哈腰，说道：多谢您老，小的感激不尽。\n");
        message_vision(CYN"$N"CYN"将衣襟松了几松，对$n"CYN"满目春意的说：英雄，以后你叫俺干什么俺就干什么。。。\n"NOR,this_object(),who);
        if( value>60 )
        	value = 60;
        set("fight_job",1);
        set("fight_time",([
        	"start" : time(),
		"time"  : value+random(value),
	]));
	this_object()->start_busy(value+1);
	return 1;
}


#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c"; 

void setname()
{
	int i;
	mapping names;
	string name,id,tmp,*ids;
	
	names = NAME_D->random_name("female");
	if( !names )
		set_name("弟子",({"dizi","di zi",}));
	else
	{
		name = names["name"];
		ids = names["id"];
		id = ids[0];
		i = strlen(name);
		if( i<=4 )
			name = sprintf("%s",name[(i-1)..i]);
		else
			name = sprintf("%s",name[(i-1)..i]);
		if( random(2) )
		{			
			if( sscanf(id,"%s %s",tmp,id)==2 )
				ids = ({"hua "+id,id,"hua","di zi"});
			else
				ids = ({"hua","di zi",});	
			name = "花"+name;			
		}
		else if( random(2) )
		{			
			if( sscanf(id,"%s %s",tmp,id)==2 )
				ids = ({"mei "+id,id,"mei","di zi"});
			else
				ids = ({"mei","di zi",});	
			name = "梅"+name;			
		}
		else
		{			
			if( sscanf(id,"%s %s",tmp,id)==2 )
				ids = ({"mu "+id,id,"mu","di zi"});
			else
				ids = ({"mu","di zi",});	
			name = "牡"+name;			
		}				
		set_name(name,ids);	
	}	
	set("my_master","ningmou xianzi");
set("gender","女性");
set("age", 25);
set("per", 35);
create_family("百花谷",2+random(3),"弟子");

set_skill("unarmed", 500+random(200));
set_skill("dodge", 500+random(200));
set_skill("parry", 500+random(200));
set_skill("force", 500+random(200));
set_skill("spells", 500+random(200));

set_skill("whip", 500+random(200));
set_skill("jueqingbian", 500+random(200));
set_skill("sword",500+random(200));
set_skill("zongheng-sword",500+random(200));
set_skill("wuyou-steps", 500+random(200));
set_skill("baihua-xianfa", 500+random(200));
set_skill("rainbow-zhi", 500+random(200));
set_skill("siji-zhang", 500+random(200));
set_skill("brightjade-force", 500+random(200));

map_skill("force", "brightjade-force");
map_skill("sword", "zongheng-sword");
map_skill("whip","jueqingbian");
map_skill("parry", "zongheng-sword");
map_skill("spells", "baihua-xianfa");
map_skill("dodge", "wuyou-steps");
map_skill("unarmed", "rainbow-zhi");
set("skillmark/zongheng-sword",({"heng","zong"})[random(2)]); 
set("skillmark/brightjade-force","yes");
}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",50000000);
	set("daoxing",50000000);
	i = 5000+random(5000);
	add_temp("apply/karma",i);
	carry_object(0,"sword",1)->wield();
	add_temp("apply/karma",-i);
}

void tiaozhan_hit(object who)
{
	object *inv,weapon;
	string msg,*msgs;
	int d,i,k;
	remove_call_out("tiaozhan_hit");
	this_object()->stop_busy();	
	if( !who || !environment() || !this_object()->is_fighting(who) )
	{
		powerup(1);
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	weapon = query_temp("weapon");
	if( !weapon || weapon->query("skill_type")!="sword" )
	{
		if( query_temp("apply/damage")<300 )
			set_temp("apply/damage",300);
		if( !who->is_busy() && random(5)==2 )
		{
			message_vision(HIC"$N"HIC"随风而舞，抬起头来朝$n"HIC"妩媚地一笑，如沉鱼落雁，倾国倾城！\n"NOR,this_object(),who);
			if( random(3) )
			{
				message_combatd(HIR"$n"HIR"神不守舍地看着$N"HIR"醉人的容颜，顿时不知所措！\n"NOR,this_object(),who);
				who->start_busy(3);
			}
			else	message_combatd(HIR"不料确被$n"HIR"看破，毫不为所动！$n"HIR"攻其不备，$P反被打了个措手不及！\n"NOR,this_object(),who);
		}
		else if( random(2) )
			command("exert hanyulingfeng");
		else if( random(2) )
		{
			msg = HIC"$N"HIC"运起无忧步法，身形恬静轻柔，飘忽不定！$N"HIC"身形突然旋转，回飞，凝神息气，一道劲飞向$n"HIC"。\n"NOR;
    		message_vision(msg,this_object(),who);
    		if( random(3) )
    		{
    			d = 300+random(500);
				who->receive_wound("kee", d, this_object(),TYPE_PERFORM);
				who->receive_damage("kee", d, this_object(),TYPE_PERFORM);
        		if( d<350 )
                	msg = HIY"结果$n"HIY"受到$N"HIY"的明玉神功气劲的攻击，闷哼一声。\n"NOR;
        		else if( d<450 )
                	msg = HIY"结果$n"HIY"被$N"HIY"的明玉神功气劲一击，「嘿」地一声退了两步。\n"NOR;
        		else if( d<650 )
                	msg = HIR"结果$n"HIY"被$N"HIY"的明玉神功气劲一重击，胸口有如受到一记重锤，连退了五六步！\n"NOR;
        		else    
        			msg = RED"结果$n"RED"被$N"RED"的明玉神功气劲击中，眼前一黑，象一捆稻草一样飞出去好几丈远！\n"NOR;
        	}
        	else	msg = CYN"可是$p看破了$P的企图，并没有上当。\n"NOR;		
			message_combatd(msg,this_object(),who);	
		}
		else
		{
			msg = HIY "$N"HIY"忽然身形一拧，越在半空，双臂急挥，双掌化十掌、百掌、千掌、万掌，犹如「四季飞花」，把$n"HIY"完全罩在掌风之中。\n"NOR;
			message_combatd(msg,this_object(),who);	
			set("actions",(: call_other, "/daemon/skill/siji-zhang", "query_action" :));
			set("SJZ",8);
			COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM);
			set("SJZ",16);
			COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM);
			set("SJZ",24);
			COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM);
			if( random(2) )
			{
				set("SJZ",9);
				COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM);
			}
			delete("SJZ");
			reset_action();
		}
	}	
	else
		QUEST_D->randomPfm(this_object());	
	call_out("tiaozhan_hit",5,who);
}

void tell_object(object who,string arg)
{
	arg = HIG"【星月挑战】"+arg+NOR;
	return efun::tell_object(who,arg);
}

void reward_ob(object who)
{
	object gift,weapon;    
	mapping skill;
	string *skills,temp,*ar;
	int i,pp;
	
	remove_call_out("tiaozhan_hit");
	if( !who || !userp(who) )
		return;

	if( time()<who->query("mark/tiaozhan/last_die")+3600      	//假死时间没到
	 || who->query("combat_exp")<10000
	 || who->query("daoxing")<10000 
	 || !who->query("obstacle/reward") )	
	{	 	
		tell_object(who,"你条件不够，无法在此地图得到任何附加奖励。\n");
		return;
	}

	if( !is_pass(who) )
	{
		who->set("mark/tiaozhan/"+query("name"),1);
		who->add("mark/tiaozhan/num",1);
	}
		
	if( random(30)>10 )
	{
		who->add("potential",10000);	
		tell_object(who,"你获得了10000点潜能。\n");
		who->add("combat_exp",-3000);
		who->add("daoxing",-3000);
		who->save();
		tell_object(who,"因为获得追加奖励，你失去了3000点的武学和道行。\n");
	}			
	
	if( random(2) )
	{
		ar = ({
				"armor","hand","cloth","kui","neck","pifeng",
				"ring","shoes","waist","wrists",
		});	
		gift = new("/d/obj/narmor/"+ar[random(sizeof(ar))]);
		i = environment()->query("number");
		i = 5000+i*500;
		i = i+who->query_kar()*30;
		i = i-pp*50;
		add_temp("apply/karma",i);
		set_skill("force",250+random(400));
		gift->init_armor(this_object());
		add_temp("apply/karma",-i);
		if( gift->move(who) )
		{
			CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->short()+HIC"。"NOR);			   
			who->add("combat_exp",-5000);
			who->add("daoxing",-5000);
			who->save();
			tell_object(who,"因为获得追加奖励，你失去了5000点的武学和道行。\n");		 
		}
		else	destruct(gift);
	}	
	else if( random(20)>5 )
	{
		gift = new(sprintf("/d/obj/equip/armor_bd%d",1+random(4)));
		if( gift->move(who) )
		{
			CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->name()+HIC"。"NOR);			   
			who->add("combat_exp",-5000);
			who->add("daoxing",-5000);
			who->save();
			tell_object(who,"因为获得追加奖励，你失去了5000点的武学和道行。\n");		 
		}
		else	destruct(gift);
	}
	return;
}

void help_kill(object who)
{
        int i,f=0;
        object *inv,npc;
        if( !who )      return;
        inv = all_inventory(environment());
        for(i=0;i<sizeof(inv);i++)
        {
                npc = inv[random(sizeof(inv))]; 
                if( npc && living(npc) && !userp(npc) //玩家或昏迷的
                 && !npc->is_fighting(who)                   //在战斗的
                 && npc!=this_object()                    //..
                 && f< 1
                 && npc->query("my_master") )
                {
                        say( sprintf("%s在旁说道：%s道友，休要惊慌，我来助你一臂之力。\n",npc->name(),this_object()->name(1)[0..1]));
                        npc->set_temp("help_kill",1);
                        npc->kill_ob(who);
                        npc->set_temp("help_kill",0);
                        f++;
                }
        }
        return;       
}

void kill_ob(object who)
{
        if( who && present(who,environment()) && userp(who)
         && !this_object()->is_fighting()
         && !query_temp("help_kill") )
        {       
                powerup(1);
                help_kill(who);
        }       
        ::kill_ob(who);
}

void heart_beat()
{
	object me = this_object();
	if( me->query("force")>100 && me->is_fighting() )
	{
     	if( query("eff_kee") < query("max_kee") )
        	QUEST_D->addEffKee(me);
        if( query("kee") < query("eff_kee") )
        	QUEST_D->addKee(me);
        if( query("sen") < query("eff_sen") )
        	QUEST_D->addSen(me);
        if( query("eff_sen") < query("max_sen") )
        	QUEST_D->addEffSen(me);
        me->stop_busy();
        QUEST_D->randomPfm(this_object());		
	}
	::heart_beat();
}

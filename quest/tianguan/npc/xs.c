#include <combat.h>
#include <ansi.h>
inherit __DIR__"n.c"; 

void setname() 
{
	set_name("大鹏明王", ({"dapeng mingwang", "dapeng", "mingwang", "wang"}));
	set("title", "雪山之祖");
	set("gender", "男性" );
	set("age", 45);
	set("per", 30);
	set("str", 30);
	set("long", "这位大鹏明王的确大有来历，说起来跟佛祖如来也有点亲戚关系，\n算是如来的“舅舅”。他不似其兄孔雀明王作恶多端，却也并非善类，\n且因其兄之故跟佛门结下深仇。生平最讨厌的就是和尚。\n");
	set("class", "yaomo");
	create_family("大雪山", 1, "祖师");
	set("rank_info/respect", "明王");
	set_skill("unarmed", 550);
	set_skill("cuixin-zhang", 550);
	set_skill("dodge", 550);
	set_skill("xiaoyaoyou", 550);
	set_skill("parry", 550);
	set_skill("sword", 550);
	set_skill("bainiao-jian", 550);
	set_skill("blade", 550);
	set_skill("bingpo-blade", 550);
	set_skill("throwing", 550);
	set_skill("force", 550);   
	set_skill("ningxie-force", 550);
	set_skill("literate", 150);
	set_skill("spells", 550);
	set_skill("dengxian-dafa", 550);
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("sword", "bainiao-jian");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");
}

int is_boss(){return 1;}

void setup()
{
	int i;
	::setup();      
	set("combat_exp",33275000);
	set("daoxing",33275000);
	i = 5000+random(5000);
	add_temp("apply/karma",i);
	if( random(2) )
	{
		carry_object(0,"sword",1)->wield();
		map_skill("parry","bainiao-jian");
	}
	else
	{
		carry_object(0,"blade",1)->wield();
		map_skill("parry","bingpo-blade");
	}
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
		powerup(0,1);
		remove_all_killer();
		if( environment() )
			all_inventory(environment())->remove_killer(this_object());
		return;
	}
	if( time()-query_temp("xiao_end") < 10 )
		command("cast niepan");
    else
    {
    	inv = all_inventory(environment());
    	k = 0;
    	for(i=0;i<sizeof(inv);i++)
    	{
    		if( inv[i] && !userp(inv[i]) && inv[i]->query_temp("invoker")==this_object() )
    			k = 1;
    	}
    	if( k==0 )
			command("cast hufa");
    }
    
	weapon = query_temp("weapon");
	if( !weapon )
	{
		if( time()>query_temp("last_tuntian")+8 )
		{
			command("cast tuntian");
			set_temp("last_tuntian",time());
		}
		else if( time()>query_temp("last_juanbi")+8 )
		{
			command("cast juanbi");
			set_temp("last_juanbi",time());
		}
		else
			QUEST_D->randomPfm(this_object());
	}	
	else if( weapon->query("skill_type")=="blade" )
	{
		if( random(3)==1 && time()>query_temp("last_qianshe")+5 )
		{
			command("perform qianshe");
			set_temp("last_qianshe",time());
		}
		else
			QUEST_D->randomPfm(this_object());
	}
	else
	{
		if( time()>query_temp("last_gui")+5 )
		{
			message_vision(HIW"$N"HIW"运转"HIR"冰谷凝血功"NOR HIW"，招式突变，"+weapon->name()+HIY"绽出万点星光,绮丽非常！\n\n" NOR,this_object());							
			msgs=({ "「"+BLINK+HIW"百灵嘤咛"+HIW"」"," 「"+BLINK+HIC"西来鹦鹉"+HIW"」" ,"「"+BLINK+HIB"乌鸦哺食"+HIW"」" ,"「"+BLINK+HIM"盈鹊飞来"+HIW"」",
					"「"+BLINK+HIY"鹰击长空"+HIW"」"," 「"+BLINK+HIC"孔雀开屏"+HIW"」" ,"「"+BLINK+HIC"凤凰涅滂"+HIW"」" ,"「"+BLINK+HIR"炎之朱雀"+HIW"」",
					"「"+BLINK+HIY"百禽归巢"+HIW"」",
			});
			k = 3+random(5);
			for(i=0;i<=k;i++)     
			{
				if( this_object() && living(this_object()) && who
				 && this_object()->is_fighting(who) )
				 {
					msg =  HIW "\n$N大喝一声："+msgs[i]+HIW"！" NOR; 
					message_combatd(msg,this_object(),who);
					set_temp("pfm_msg",1);
					d = COMBAT_D->do_attack(this_object(),who,query_temp("weapon"),TYPE_PERFORM);
					d-= who->query_temp("apply/armor");
					if( d<50 ) d = 50;
					who->receive_wound("kee",d/2,this_object(),TYPE_PERFORM); 
					who->receive_damage("kee",d ,this_object(),TYPE_PERFORM); 
					COMBAT_D->report_status(who,1);
					COMBAT_D->report_status(who); 
					set_temp("pfm_msg",0);
 				}				
			}
			set_temp("last_gui",time());
		}
		else
			QUEST_D->randomPfm(this_object());
	}				
	call_out("tiaozhan_hit",3+random(2),who);
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
		
	if( random(30)>17 )
	{
		who->add("potential",50000);	
		tell_object(who,"你获得了50000点潜能。\n");
		who->add("combat_exp",-3000);
		who->add("daoxing",-3000);
		who->save();
		tell_object(who,"因为获得追加奖励，你失去了3000点的武学和道行。\n");
	}			
	
	pp = who->query_temp("tiaozhan_weapon_get");
	if( random(pp)==0 )
	{
		ar = ({ "sword","blade",});	
		gift = new("/d/obj/nweapon/"+ar[random(sizeof(ar))]);
		i = environment()->query("number");
		i = 2000+i*500;
		i = i+who->query_kar()*30;
		i = i-pp*50;
		add_temp("apply/karma",i);
		set_skill("force",200+random(150));
		gift->init_weapon(this_object());
		add_temp("apply/karma",-i);
		if( gift->move(who) )
		{
			CHANNEL_D->do_channel(environment(),"chat",who->name(1)+"于"+environment()->query("short")+"打败"+name()+"，得到了"+gift->short()+HIC"。"NOR);			   
			who->add_temp("tiaozhan_weapon_get",1);
			who->add("combat_exp",-5000);
			who->add("daoxing",-5000);
			who->save();
			tell_object(who,"因为获得追加奖励，你失去了5000点的武学和道行。\n");		 
		}
		else	destruct(gift);
	}	
	else if( random(20)>13 )
	{
		gift = new(sprintf("/d/obj/equip/armor_bd%d",1+random(4)));
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
	return;
}
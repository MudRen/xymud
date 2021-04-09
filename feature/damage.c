// damage.c
#include <ansi.h>
#include <dbase.h>
#include <login.h>
#include <combat.h>
#include <move.h>

void remove_faint(object me);
int ghost = 0;
int xuruo = 0;

int is_ghost() { return ghost; }
void set_ghost(){ghost=1;}
int is_xuruo() { return xuruo; }

varargs void powerup(int flag,int no_condition)
{
	if( !objectp(this_object()) )
        	return;
	if( flag && flag>=1 )
        	message_vision(HIG"$N"HIG"从怀里小心翼翼的拿出一颗云丹送入嘴中，果然见$P脸上慢慢泛出红光，法力和内力到了极限！\n"NOR,this_object());
        set("eff_kee",this_object()->query_maxkee());
	set("kee",this_object()->query_maxkee());
        set("eff_sen",this_object()->query_maxsen());
	set("sen",this_object()->query_maxsen());
	if( flag && flag>=1 )
	{
		set("force",(int)this_object()->query_maxforce());
		set("mana",(int)this_object()->query_maxmana());		
	}
	else
	{
		set("force",(int)this_object()->query_maxforce());
		set("mana",(int)this_object()->query_maxmana());		
	}
	if( !no_condition || no_condition<1 )
        	this_object()->clear_condition();
}

int self_purge()
{
	object me=this_object();

	if( !userp(me) ) return 0;
	if( (int)me->query_maxkee() > 0 
  	 && (int)me->query_maxsen() > 0 ) 
        	return 0;
	set_heart_beat(0);
	ghost =1;
	me->move("/d/death/block.c");
	CHANNEL_D->do_channel(me, "rumor", me->query("name")+ "因为年纪太大，心力交瘁，不幸与世长辞，永远离开了我们！"); 
	return 1;
}

void gameover()
{
	object me = this_object();
	if( !userp(me) ) return;
	me->move("/d/death/block.c");
	if( !me->query("life/death_announced") )
        {
	        me->set("life/death_announced", 1);
        	CHANNEL_D->do_channel(load_object(COMBAT_D), "rumor", me->query("name")+ "寿终正寝，永远地离开了我们。");
        }           
}

int check_gameover()
{//weiqi, 981231
	object me = this_object();
	if( wizardp(me) ) return 0;
	if( !userp(me) ) return 0;
	if( me->query_life()==-1 )
		return 0;
	if( (me->query("age") <= me->query("life/life_time")) 
   	 || me->query("life/live_forever") ) 
        	return 0;
	gameover();
	return 1;
}

void announce_live_forever(string reason)
{
	int age;
	object me = this_object();
	if( !reason ) return;
	if( me->query("life/live_forever_announced") ) 
        	return;
	me->set("life/live_forever_announced", 1);
	me->set("life/live_forever", 1);
 	age = query("age");
 	//look的年龄
	if( age>query("fake_age") ) 
		age = query("fake_age");
	else    set("fake_age", age);	
	message_vision(HIY"只听一阵仙乐缥缈，一驾五彩云车从天缓缓而降。\n"NOR, me);
	message_vision(HIY"玉皇大帝从车上立起身来对$N"HIY"一拱手：恭喜！恭喜！\n"NOR,me);
	message("channel:chat",HIC"【长生不老】玉皇大帝(Yuhuang)："+reason+NOR"\n",users());
	message_vision(HIY"玉皇大帝一挥手，云车渐渐淡去...\n"NOR,me);
	return;
}

varargs int receive_damage(string type, int damage, object who,mixed attack_type)
{
	string str;
	object hufa;
	int val;

	if( damage < 0 ) 
		error("F_DAMAGE: 伤害值为负值。\n");
	if( type!="kee" && type!="sen" )
		error("F_DAMAGE_D: 伤害种类错误( 只能是 kee,sen 其中之一 )。\n");
	if( !attack_type )
		attack_type = TYPE_COMBAT;
	if( who && objectp(who) && who!=this_object() )
	{
		if( environment() && environment()->query("leitai") )
			damage = damage/5+1;		 
	}			
	if( objectp(who) && who!=this_object() ) 
	{
		if(objectp(who->query_temp("invoker")))
			who=who->query_temp("invoker");
	    	set_temp("last_damage_from", who);
	}
	if( who && who!=this_object() && who->is_fighting(this_object()) )
	{
		if( this_object()->imm_damage(attack_type) )
			return 0;
	}
//护法抵消伤害	
	hufa = this_object()->query_temp("invocation");
	if( hufa && objectp(hufa) && damage<hufa->query(type)/2
	&& living(hufa) && present(hufa,environment())  
	&& who && who!=this_object() 
	&& hufa->query("receive_damage") )
	{
		damage/= 2;
		hufa->receive_damage(type,damage,who,attack_type);
		if( stringp(str=hufa->query_hufa_msg()) )
			message_combatd(str,this_object(),who);
	}
	if( damage<1 )  damage = 1;	
	
	val = (int)query(type) - damage;

	if( val >= 0 ) set(type, val);
	else 
	{
		set( type, -1 );
	  	if( living(this_object()) && objectp(who)
	  	 && userp(who) && !query_temp("last_fainted_from") )
	  	 {
	    		set_temp("last_fainted_from",who->query("id"));
	    		if(userp(this_object()))
	      			call_out("remove_faint",60,this_player());
		}
        }
	set_heart_beat(1);
	return damage;
}

void remove_faint(object me)
{  
	if(me) 
		me->delete_temp("last_fainted_from"); 
}

varargs int receive_wound(string type, int damage, object who,mixed attack_type)
{
	object hufa;
	string str;
	int val;
	int val1;

	if( damage < 0 ) 
		error("F_DAMAGE: 伤害值为负值。\n");
	if( type!="kee" && type!="sen" )
		error("F_DAMAGE_W: 伤害种类错误( 只能是 kee,sen 其中之一 )。\n");
	if( !attack_type )
		attack_type = TYPE_COMBAT;

	if( objectp(who) && who!=this_object() )
	{
		if(objectp(who->query_temp("invoker")))
			who=who->query_temp("invoker");
	    	set_temp("last_damage_from", who);
	}
	if( who && objectp(who) && who!=this_object() )
	{
		if( environment(this_object())
		 && environment(this_object())->is_leitai() )
			damage = damage/6+1;		 
	}			
	if( who && who!=this_object() && who->is_fighting(this_object()) )
	{
		if( this_object()->imm_eff_damage(attack_type) )
			return 0;
	}
//护法抵消伤害	
	hufa = this_object()->query_temp("invocation");
	if( hufa && objectp(hufa) && damage<hufa->query("eff_"+type)/3
	&& living(hufa) && present(hufa,environment())  
	&& who && who!=this_object() 
	&& hufa->query("receive_wound") )
	{
		damage = damage-damage/3;
		hufa->receive_wound(type,damage,who,attack_type);
		if( stringp(str=hufa->query_hufa_msg()) )
			message_combatd(str,this_object(),who);
	}
	if( damage<1 )  damage = 1;	
	
	val = (int)query("eff_" + type) - damage;
	val1= (int)query(type);

	if( val >= 0 ) set("eff_" + type, val);
	else 
	{
		if(val1>100) 
		{
			set( "eff_" + type, 0);
			set(type,-1);
			val1=-1;
			val=0;
	    	} 
	    	else 
	    	{
			set( "eff_" + type, -1 );
			val = -1;
	    	}
		if( living(this_object()) && objectp(who)
		 && userp(who) 
		 && !query_temp("last_fainted_from") )
		{
			set_temp("last_fainted_from",who->query("id"));
			if(userp(this_object()))
		  		call_out("remove_faint",60,this_player());
		}
	}

	if( val1 > val ) set(type, val);
	set_heart_beat(1);
	return damage;
}

int receive_heal(string type, int heal)
{
	int pp,val;
	if( heal < 0 ) error("F_DAMAGE: 恢复值为负值。\n");
	if( type!="kee" && type!="sen" )
		error("F_DAMAGE_H: 伤害种类错误( 只能是 kee,sen 其中之一 )。\n");
	if( type=="kee" )
		heal = heal*(100+(int)this_object()->query_temp("apply/receive_heal_kee"))/100;
	else	heal = heal*(100+(int)this_object()->query_temp("apply/receive_heal_sen"))/100;
//医药	治疗效果+5%
	if( this_object()->query_skill("yiyao",2)>100 )
	{
		pp = 5;
		pp+= (this_object()->query_skill("yiyao",1)-100)/300;
		heal+= heal*pp/100;
	}	
	val = (int)query(type) + heal;
	if( val > (int)query("eff_" + type) ) 
		set(type, (int)query("eff_" + type));
	else set( type, val );
	return heal;
}

int receive_curing(string type, int heal)
{
	int pp,max, val;
	if( heal < 0 ) error("F_DAMAGE: 恢复值为负值。\n");
	if( type!="kee" && type!="sen" )
		error("F_DAMAGE_C: 伤害种类错误( 只能是 kee,sen 其中之一 )。\n");
	val = (int)query("eff_" + type);
	if( type=="kee" )
		max = (int)this_object()->query_maxkee();
	else	max = (int)this_object()->query_maxsen();
	if( type=="kee" )
		heal = heal*(100+(int)this_object()->query_temp("apply/receive_curing_kee"))/100;
	else	heal = heal*(100+(int)this_object()->query_temp("apply/receive_curing_sen"))/100;	
//医药	治疗效果+5%
	if( this_object()->query_skill("yiyao",2)>100 )
	{
		pp = 5;
		pp+= (this_object()->query_skill("yiyao",1)-100)/300;
		heal+= heal*pp/100;
	}			
	if( val + heal > max ) 
	{
		set("eff_" + type, max);
		return max - val;
	} 
	else 
	{
		set( "eff_" + type, val + heal);
		return heal;
	}
}

// snowcat feb 8 1998 
void remove_ride ()
{
	object rider, ridee;
	if( ridee = query_temp("ridee") )
        	ridee->delete_temp("rider");
	delete_temp("ridee");
	add_temp("apply/dodge",-query_temp("ride/dodge"));
	set_temp("ride/dodge",0);
	if( rider = query_temp("rider") )
        	rider->remove_ride();
	delete_temp("rider");
}

void unconcious()
{
	int t;
	object defeater;

	if(!living(this_object())) 
		return;
	if(this_object()->is_busy()) 
		this_object()->interrupt_me();
	if(this_object()->run_override("unconcious")) 
		return;
	if( objectp(defeater = query_temp("last_damage_from")) )
	{
		if( !this_object()->is_killing(defeater->query("id"))
		 && !defeater->is_killing(this_object()->query("id")) )
		{
			if( userp(this_object()) && !userp(defeater) )
				defeater->combat_win(this_object());
        		else if( userp(defeater) && !userp(this_object()) )
				this_object()->combat_lose(defeater);
		}			
	}        				
	if( environment() && environment()->query("alternative_die") ) 
        {
        	if( environment()->alternative_die(this_object())==0 )
        		return;
        }
	if( wizardp(this_object()) && query("env/immortal") ) 
	{
		powerup(1,1);
        	return;
        }
	if( objectp(defeater = query_temp("last_damage_from")) )
        	COMBAT_D->winner_reward(defeater, this_object());
	this_object()->remove_all_enemy();
	remove_ride();
	message("system", HIR "\n你的眼前一黑，接着什么也不知道了．．．\n\n" NOR,this_object());
	this_object()->disable_player(" <昏迷不醒>");
	set("kee", 0);
	set("sen", 0);
	set_temp("block_msg/all", 1);
	COMBAT_D->announce(this_object(), "unconcious");
	t = random(100 - query("con")) + 30;
	if( t<15 )
		t = 15;
	call_out("revive",t );
}

varargs void revive(int quiet)
{
	string room;
	object ob;
	remove_call_out("revive");

        this_object()->start_no_move(1);
	if(this_object()->is_busy()) 
		this_object()->start_busy(1);
	while( environment()->is_character() )
		this_object()->move(environment(environment()));
	this_object()->enable_player();
	if( !quiet ) 
	{
		COMBAT_D->announce(this_object(), "revive");
		set_temp("block_msg/all", 0);
		message("system", HIY "\n慢慢地你终于又有了知觉．．．\n\n" NOR,this_object());
	} 
	else	set_temp("block_msg/all", 0);
	while( environment()&& environment()->is_character() )
        	this_object()->move(environment(environment()));
// 不能把 npc 搬进安全区。
	if( !userp(this_object())
          && environment()->query("no_fight")
          && stringp(room = query("startroom"))
          && base_name(environment()) != room )
	{
        	ob = find_object(room);
                if( ob )
                	this_object()->return_home(ob);
		else
		{
                	tell_object(environment(), this_object()->name()+"匆匆忙忙的走了。\n");
                        destruct(this_object());
		}
	}
}

void lose_inventory()
{
	int i,k,p;
	object obj,*inv;
	inv = all_inventory(this_object());
	k = sizeof(inv);
	if( k>0 )
	{
		if( this_object()->query_condition("no_pk_time") )
			p = k;
		else if( random(this_object()->query_kar())/10>5 )
			p = random(5);
		else	p = k/2+random(k/2);
		if( p>k )
			p = k;		
		p = p/2+random(p/2);
		if( p>0 )
		{
			while(p--)
			{
				inv = all_inventory(this_object());
				obj = inv[random(sizeof(inv))];
				if( !obj || obj->is_character() || obj->query("no_get") )
					continue;
				if( obj->query("owner_id")==getuid(this_object())
				 || inherits(F_ONEOWNER,obj)>0 )
				{
                			tell_object(this_object(), HIB+"你看到" + inv[i]->query("name") +HIB + "破空而去，慢慢消失在天际．．．\n"+NOR);
                			destruct( inv[i] );
                		}
                		else
                		{
                			message_vision(HIY"\n$N"HIY"掉落了"+obj->name()+HIY"。\n"NOR,this_object());
                			if( !obj->move(environment()) )
                				destruct(obj);
                		}				
			}	
		}
	}	
}

void die()
{
	object corpse, killer,me, guai;
	int i;
	string last_fainted_from, str;
	int exp, pot, score;

	me = this_object();

	if( me->is_ghost() )
		return;	
	if(this_object()->run_override("die")) 
		return;		
	//神通：起死回生
	if( this_object()->query_skill("qisi-huisheng",2)>0 )
	{
		i = this_object()->query_skill("qisi-huisheng",2);
		i*= 7;
		if( i>=43200 )
			i = 43200;
		i = 86400-i;
		if( time()>=this_object()->query("death/last_fenghuang")+i )
		{
			this_object()->set("death/last_fenghuang",time());
			message_vision(HIR"\n$N"HIR"浑身忽冒起炽热的烈火，隐约间一道清亮的凤凰鸣叫一声响起，$N"HIR"顿时若浴火重生一般！"NOR"\n\n",this_object());
			this_object()->powerup(0,1);
			return;
		}
	}        	

	if( objectp(killer = query_temp("last_damage_from")) )
	{
		if( !this_object()->is_killing(killer->query("id"))
		 && !killer->is_killing(this_object()->query("id")) )
		{
			if( userp(this_object()) && !userp(killer) )
				killer->combat_win(this_object());
        		else if( userp(killer) && !userp(this_object()) )
				this_object()->combat_lose(killer);
		}			
	}  		
	if( query_temp("last_fainted_from") ) 
        	last_fainted_from=query_temp("last_fainted_from");
	if( last_fainted_from ) 
        	set_temp("last_fainted_from",last_fainted_from);
	if( environment() && environment()->query("alternative_die") ) 
        {
        	if( environment()->alternative_die(this_object())==0 )
        		return;
        }
	if( !living(this_object()) ) 
        	revive(1);
	if( wizardp(this_object()) && query("env/immortal") ) 
        	return;
	//
	lose_inventory();
	//
	COMBAT_D->announce(this_object(), "dead");
	if( me->query("force")<0 )     me->set("force",0);
	if( me->query("mana")<0 )      me->set("mana",0);
	if( me->query("rulaitask/get") )
        {
        	guai = me->query("rulaitask/guai");        
        	if( guai==me->query_temp("last_damage_from") || guai==me->query_temp("last_opponent") )
                {
                	me->set("eff_kee",me->query_maxkee());
                	me->set("eff_sen",me->query_maxsen());
                	me->set("kee",me->query_maxkee()/3);
                	me->set("sen",me->query_maxsen()/3);
                	if((int)me->query("combat_exp")>100000000)       
                        {
                        	me->add("combat_exp",-20000);
                        	me->add("daoxing",-20000);
                        }
                	else if((int)me->query("combat_exp")>50000000)       
                        {
                        	me->add("combat_exp",-15000);
                        	me->add("daoxing",-15000);
                        }
                	else if((int)me->query("combat_exp")>10000000)       
                        {
                        	me->add("combat_exp",-10000);
                        	me->add("daoxing",-10000);
                        }
                	else if((int)me->query("combat_exp")>5000000)       
                        {
                        	me->add("combat_exp",-5000);
                        	me->add("daoxing",-5000);
                        }
                	else    
                	{
                        	me->add("combat_exp",-2000);
                        	me->add("daoxing",-2000);
                        }
                	me->add("rulaitask_log/die",1);
                	me->delete("rulaitask/get");
                	me->set("rulaitask/fail",1);
                	str = HIR+me->name()+NOR HIM"不幸被杀死了，幸好如来佛及时出手相救，才捡回一命。"NOR;
                	CHANNEL_D->do_channel(me,"rumor",str);
                	remove_ride();
                	me->move("/d/qujing/lingshan/daxiong");
                	message_vision(HIY"如来佛一伸左手把$N"HIY"的魂魄从地府里拉了回来，再一伸右手不知道从哪里把$P的尸体抓了回来，接着两手一合，硬生生地把魂魄逼回身体。\n"NOR,me);
                	me->unconcious();
                	return;
                }
        }

	if( (int)this_object()->query_maxkee()>0 
  	 && (int)this_object()->query_maxsen()>0 ) 
	{
        	if( objectp(killer = query_temp("last_damage_from")) ) 
                {
	                set_temp("my_killer", killer->query("id"));
        	        COMBAT_D->killer_reward(killer, this_object());
                	this_object()->clear_condition();
                } 
        	else if( userp(this_object()) ) 
                {
                	COMBAT_D->victim_penalty(this_object());
                	if( stringp(str=this_object()->query_temp("death_msg")) )  
                        	str = this_object()->name(1)+str;
                	else    str = this_object()->name(1)+"莫名其妙地死了。\n";
			this_object()->delete_temp("death_msg");                	
                	COMBAT_D->announce(this_object(), "death_rumor", str);
                }
        	remove_ride();
        	if( !userp(this_object()) && !query("no_corpse") )
        	{
        		if( objectp(corpse = CHAR_D->make_corpse(this_object(), killer)) )
                		corpse->move(environment());
                }		
        }

	this_object()->remove_all_killer();
	all_inventory(environment())->remove_killer(this_object());
	this_object()->dismiss_team();
	this_object()->delete_temp("pfm_action");
	this_object()->delete_temp("cast_action");
        this_object()->delete_temp("invocation");	
        this_object()->set("last_invocation",time());
	if( this_object()->self_purge() ) 
        	return;
	if( userp(this_object()) ) 
        {
        	set("kee", 1);  set("eff_kee", 1);
        	set("sen", 1);  set("eff_sen", 1);
        	if( !this_object()->query("life/life_time") ) 
                	this_object()->set("life/life_time", 60);
        	if( !this_object()->query("life/no_death_decrease") )
                	this_object()->set("life/life_time", (int)this_object()->query("life/life_time")-1);
        	if( check_gameover() ) return;
        	this_object()->clear_condition();
        	ghost = 1;
        	this_object()->move(DEATH_ROOM);
        	DEATH_ROOM->start_death(this_object());
        } 
	else    destruct(this_object()); 
}

void reincarnate()
{
	ghost = 0;
//	command("drop all");
	set("eff_kee", this_object()->query_maxkee());
	set("eff_sen", this_object()->query_maxsen());
}

int max_food_capacity() 
{ 
	int final;
	final=(int)query_weight()/200;
	if(final < 100 )
        final=100;
	return final;
}

int max_water_capacity() 
{   
	int final;
	final=(int)query_weight()/200;
	if( final< 100 ) 
        	final=100;
	return final; 
}

//增加一个食物饮水扣除的函数，从heal_up中独立出来
void food_heal_up()
{
	int lvl,cost,t,p;
	object ob = this_object();
	if( !ob || ( environment() && environment()->query("no_time") ) ) 
		return;
	if( !userp(ob) || sizeof(query_temp("no_heal_up")) )
		return;
	//饮食损耗随着修为增加而递减		
	lvl = ob->query_level();
	cost = 20-lvl/10;
	if( cost<=0 )
		return;
	t = 10;
	p = ob->query_skill("bigu",1)/100;
	t = t+p;
	if( time()<ob->query_temp("last_food_heal_up")+t )
		return;
	ob->set_temp("last_food_heal_up",time());
	if( ob->query("food")>=cost )
		ob->add("food",-cost);
	else	ob->set("food",0);
	if( ob->query("water")>=cost )	
		ob->add("water",-cost);
	else	ob->set("water",0);
	ob->save(1);	
}


int heal_up()
{
	int update_flag, i,p;
	mapping my;
	object ob = this_object();
	if( !ob || ( environment() && environment()->query("no_time") ) ) 
		return -1;

	update_flag = 0;
	my = query_entire_dbase();
	// mon 01/23/99
	if( sizeof(query_temp("no_heal_up")) )
		return update_flag;

	// mon 0122/99
  	if( !userp(this_object()) 
  	 && this_object()->is_fighting() 
  	 && !my["allow_heal_up"] ) 
		return -1;
	
	//饮食损耗
	food_heal_up();

	if( my["water"] >5 ) 
	{
		update_flag++;
		if( my["force"]<ob->query_maxforce() )		
			my["force"]+= ob->query_skill("force")/60+ob->query_temp("apply/receive_force");
		if( my["mana"]<ob->query_maxmana() )		
			my["mana"]+= ob->query_skill("spells")/60+ob->query_temp("apply/receive_mana");
	}
	else
	{
		update_flag++;
		if( my["mana"]>0 )
			my["mana"]-= 1;
	}
	if( my["food"] >5 )
	{
		p = ob->query_con()/5+random(ob->query_kar())/10;
		if( ob->query_skill("butian-yuri",2)>100 )
		{
			i = (ob->query_skill("butian-yuri",1)-100)/150+20;
			p = p*(100+i)/100;	
		}
		p+= ob->query_temp("apply/receive_kee");
		my["kee"] += p;
		if( my["kee"] >= my["eff_kee"] ) 
		{
			my["kee"] = my["eff_kee"];
			if( my["eff_kee"] < ob->query_maxkee() )	
			{ 
				my["eff_kee"] ++; 
				update_flag++; 
			}
		}
		else	update_flag++;

		p = ob->query_spi()/5+random(ob->query_kar())/10;
		if( ob->query_skill("huakai-qingke",2)>100 )
		{
			i = (ob->query_skill("huakai-qingke",1)-100)/150+20;
			p = p*(100+i)/100;	
		}
		p+= ob->query_temp("apply/receive_sen");
		my["sen"] += p;
		if( my["sen"] >= my["eff_sen"] ) 
		{
			my["sen"] = my["eff_sen"];
			if( my["eff_sen"] < ob->query_maxsen() )	
			{ 
				my["eff_sen"] ++; 
				update_flag++; 
			}
		}
		else	update_flag++;
	}
	else
	{
		update_flag++;
		if( my["force"]>0 )
			my["force"]-= 1;
	}
	return update_flag;
}

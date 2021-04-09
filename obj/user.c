// user.c
#pragma save_binary

#include <origin.h>
#include <user.h>
#include <command.h>
#include <ansi.h>

inherit CHARACTER;
inherit F_AUTOLOAD;
inherit F_SAVE;
inherit F_BACKUP;
inherit F_ENCODING;

nosave int last_age_set;

mapping xy_job;
mapping xy_job_level;

//升级设置
mapping Last_level_up;

void create()
{
	::create();
	set_name("使用者物件", ({ "user object", "user", "object" }) );
	if( !xy_job ) xy_job = ([ ]);
	if( !Last_level_up ) Last_level_up = ([ ]);
}

varargs void remove_level_up(int v) //巫师测试用 
{
	if( !v || v>5 )
	{
		Last_level_up = ([]);
		return;		
	}
	switch(v)
	{
		case 1 : 
			if( !undefinedp(Last_level_up["a"]) )
				map_delete(Last_level_up,"a");
			return;	
		case 2 : 
			if( !undefinedp(Last_level_up["b"]) )
				map_delete(Last_level_up,"b");
			return;	
		case 3 : 
			if( !undefinedp(Last_level_up["c"]) )
				map_delete(Last_level_up,"c");
			return;	
		case 4 : 
			if( !undefinedp(Last_level_up["d"]) )
				map_delete(Last_level_up,"d");
			return;	
		default : 
			if( !undefinedp(Last_level_up["e"]) )
				map_delete(Last_level_up,"e");
			return;	
	}
}

void terminal_type(string term_type)
{
	set_temp("terminal_type", term_type);
	message("system", "终端机型态设定为 " + term_type + "。\n", this_object());
}

void reset()
{
	if( (int)query("potential") - (int)query("learned_points") < 10 )
		add("potential", 1);
	if( (int)query("thief") > 0 )
		add("thief", -1 );
}

string query_save_file()
{
	string id;
	id = query("id", 1);
	if( !id ) id = geteuid();
	if( !id ) id = getuid();
	if( !stringp(id) ) return 0;
	return sprintf(DATA_DIR "user/%c/%s", id[0], id);
}

int save(int raw)
{
	int res;

	if(!raw) save_autoload();
	res = ::save();
	if(!raw) clean_up_autoload();		// To save memory
	return res;
}

int backup()
{
	int res;
	save_autoload();
	res = ::backup();
	clean_up_autoload();		// To save memory
	return res;
}

void update_age()
{
	object me = this_object();
        int age, newtime,life,die=0;
	object env;
	
    	if(environment()&&environment()->query("no_time"))
    	{
        	last_age_set = time();
        	return;
    	}
	if( !last_age_set ) last_age_set = time();
	add("mud_age", time() - last_age_set);
	last_age_set = time();
	set("age", 14 + (int)query("age_modify")/86400 + (int)query("mud_age")/ 86400);
    	if((int)query("mud_age")%86400 < 10 && query("age") > query("last_birthday_ask") )
	{
    		if(query("age")<16) 
    			return;
		message("chat",HIY"【小雨西游】生辰精灵：祝贺"HIR+this_object()->query("name")+HIY"生日快乐！\n"NOR,users());
        	tell_object(this_object(),HIG"祝你生日快乐！恭喜你将获得特别的生日礼物。\n"NOR);
        	tell_object(this_object(),"去精灵楼找生辰精灵要生日礼物去吧。\n");
        	this_object()->set("birthday_ask",1);
        	this_object()->set("last_birthday_ask",query("age"));
	}
//寿元
	life = this_object()->query_life();
	if( life==-1 )
		return;
	if( !query("life/init_life_time") )
	{
         	set("life/life_time",life);
         	set("life/init_life_time",life);
        }
        else if( query("life/init_life_time")>=life )
        	;
        else	
	{
		newtime = life-query("life/init_life_time");
		set("life/init_life_time",life);
		add("life/life_time",newtime);
        }		
}

void setup()
{
	mapping	fabao_map;
	string  *fabao_list, *id_list, *t_list;
	string jiasha_id;
	int		i;
	object	newob;
	string  fabao_id;

	update_age();

	::setup();
	restore_autoload();
}

private void user_dump(int type)
{

	switch(type) 
	{
		case DUMP_NET_DEAD:
			tell_room( environment(), query("name") + "断线超过"+ chinese_number(NET_DEAD_TIMEOUT/60)+ "分钟，自动退出这个世界。\n");
			QUIT_CMD->main(this_object(),"",1);
			break;
		case DUMP_IDLE:
      			if(!wizardp(this_object()) && environment(this_object())->query("short")!="发呆室" )
      			{
				tell_object( this_object(), "对不起，您已经发呆超过 " + IDLE_TIMEOUT/60 + " 分钟了，请下次再来。\n");
				tell_room( environment(), "一阵风吹来，将发呆中的" + query("name")+ "化为一堆飞灰，消失了。\n", ({this_object()}));
				QUIT_CMD->main(this_object(),"",1);
				return;
                      	}
	              	break;
		default: return;
	}
}

private void net_dead()
{
	object link_ob;

	if( objectp(link_ob = query_temp("link_ob")) )  
	{
		if(!link_ob->is_character()) 
		{
	    		link_ob->set("last_on", time());
	    		link_ob->set("last_from", query_ip_number(this_object()));
	    		link_ob->save();
	  	}
        }
	if( userp(this_object()) ) 
		CHANNEL_D->do_channel(this_object(), "sys", "断线了。",0,1);

	set_temp("netdead_ip", query_ip_number(this_object()));
	remove_call_out("do_net_dead");
    	call_out("do_net_dead",15);
}

private void do_net_dead()
{
	object link_ob;

	if(!this_object()) 
		return;
	if(interactive(this_object())) 
		return;
	set_heart_beat(0);
	if( objectp(link_ob = query_temp("link_ob")) )  
		destruct(link_ob);
	add_netdead_enemy();
	remove_all_enemy();
	set_temp("netdead", 1);
	if( userp(this_object()) ) 
	{
		call_out("user_dump", NET_DEAD_TIMEOUT, DUMP_NET_DEAD);
		if( !this_object()->query("env/invisibility") && !this_object()->is_yinshen() )
			tell_room(environment(), query("name") + "断线了。\n", this_object());
	    	CHANNEL_D->do_channel(this_object(), "sys", "断线了。");
	} 
	else 	QUIT_CMD->main(this_object(),"",1);
}

// reconnect: called by the LOGIN_D when a netdead player reconnects.
void reconnect()
{
	set_heart_beat(1);
	set_temp("netdead",0);
	remove_netdead_enemy();
	remove_call_out("user_dump");
	remove_call_out("do_net_dead");
	tell_object(this_object(), "重新连线完毕。\n");
}

void gift_lose()
{
	int i,lvl;
	int gin,effgin,maxgin;
	string *gifts,tmp;
	mapping old,prop = ([
		"str" : "膂力",	"cor" : "胆识",
		"int" : "悟性",	"spi" : "灵性",
		"cps" : "定力",	"per" : "魅力",
		"con" : "根骨",	"kar" : "福缘",
	]);
	if( !Last_level_up ) Last_level_up = ([ ]);		
	lvl = this_object()->query_level();
	if( lvl<40 )
	{
		if( undefinedp(Last_level_up["a"]) )
			return;
		else
		{
			if( undefinedp(Last_level_up["a"][lvl]) )
				return;
			else	old = Last_level_up["a"][lvl];
		}	
	}	
	else if( lvl<80 )
	{
		if( undefinedp(Last_level_up["b"]) )
			return;
		else
		{
			if( undefinedp(Last_level_up["b"][lvl]) )
				return;
			else	old = Last_level_up["b"][lvl];
		}	
	}	
	else if( lvl<120 )
	{
		if( undefinedp(Last_level_up["c"]) )
			return;
		else
		{
			if( undefinedp(Last_level_up["c"][lvl]) )
				return;
			else	old = Last_level_up["c"][lvl];
		}	
	}	
	else if( lvl<160 )
	{
		if( undefinedp(Last_level_up["d"]) )
			return;
		else
		{
			if( undefinedp(Last_level_up["d"][lvl]) )
				return;
			else	old = Last_level_up["d"][lvl];
		}	
	}	
	else
	{
		if( undefinedp(Last_level_up["e"]) )
			return;
		else
		{
			if( undefinedp(Last_level_up["e"][lvl]) )
				return;
			else	old = Last_level_up["e"][lvl];
		}	
	}	
	if( !old || !mapp(old) )
		return;
	gifts = keys(old);	
	if( !gifts || !arrayp(gifts) || sizeof(gifts)<1 )
		return;
		
	for(i=0;i<sizeof(gifts);i++)
	{
		if( old[gifts[i]]>0 )
		{
			this_object()->add(gifts[i],-old[gifts[i]]);
			if( !undefinedp(prop[gifts[i]]) )
				tell_object(this_object(),HIY"【系统】你的〖 "HIG+prop[gifts[i]]+HIY" 〗减少了 "HIR+(old[gifts[i]])+HIY" 点。\n"NOR);
		}	
	}
	
	maxgin = this_object()->query("max_gin");
	effgin = this_object()->query("eff_gin");
	gin = this_object()->query("gin");
	gin = effgin-gin;
	effgin = maxgin-effgin;
	
	this_object()->add("max_gin",-10);
	this_object()->set("eff_gin",this_object()->query("max_gin")-effgin);
	this_object()->set("gin",this_object()->query("eff_gin")-gin);
	tell_object(this_object(),HIY"【系统】你的〖 "HIG"活力"HIY" 〗减少了 "HIR+10+HIY" 点。\n"NOR);	
}

varargs int reward_gift(int v)
{
	int *rewards,i,k,lvl,newf=0;
	int gin,effgin,maxgin;
	string fam,*gifts;
	mapping m_gift,prop;
	object me = this_object();
	if( !living(me) || !interactive(me) || !environment(me) )
		return 0;
	if( !v || v<=0 )
		v = 1;
	gifts = ({"str","cor","int","spi","cps","per","con","kar",});
	prop = ([
		"str" : "膂力",	"cor" : "胆识",
		"int" : "悟性",	"spi" : "灵性",
		"cps" : "定力",	"per" : "魅力",
		"con" : "根骨",	"kar" : "福缘",
	]);
	if( !Last_level_up ) Last_level_up = ([ ]);
	lvl = me->query_level()+1;
	if( lvl<40 )
	{
		if( undefinedp(Last_level_up["a"]) )
		{
			newf = 1;
			Last_level_up["a"] = ([ lvl : ([ "str" : 0,"cor" : 0,"int" : 0,"spi" : 0,"cps" : 0, "per" : 0, "con" : 0, "kar" : 0,]),]);	
		}
		else	
		{
			if( undefinedp(Last_level_up["a"][lvl]) )
			{
				newf = 1;
				Last_level_up["a"][lvl] = ([ "str" : 0,"cor" : 0,"int" : 0,"spi" : 0,"cps" : 0, "per" : 0, "con" : 0, "kar" : 0,]);
			}
			else	m_gift = Last_level_up["a"][lvl];
		}
	}
	else if( lvl<80 )
	{
		if( undefinedp(Last_level_up["b"]) )
		{
			newf = 1;
			Last_level_up["b"] = ([ lvl : ([ "str" : 0,"cor" : 0,"int" : 0,"spi" : 0,"cps" : 0, "per" : 0, "con" : 0, "kar" : 0,]),]);	
		}
		else
		{
			if( undefinedp(Last_level_up["b"][lvl]) )
			{
				newf = 1;
				Last_level_up["b"][lvl] = ([ "str" : 0,"cor" : 0,"int" : 0,"spi" : 0,"cps" : 0, "per" : 0, "con" : 0, "kar" : 0,]);
			}
			else	m_gift = Last_level_up["b"][lvl];
		}
	}
	else if( lvl<120 )
	{
		if( undefinedp(Last_level_up["c"]) )
		{
			newf = 1;
			Last_level_up["c"] = ([ lvl : ([ "str" : 0,"cor" : 0,"int" : 0,"spi" : 0,"cps" : 0, "per" : 0, "con" : 0, "kar" : 0,]),]);	
		}	
		else
		{
			if( undefinedp(Last_level_up["c"][lvl]) )
			{
				newf = 1;
				Last_level_up["c"][lvl] = ([ "str" : 0,"cor" : 0,"int" : 0,"spi" : 0,"cps" : 0, "per" : 0, "con" : 0, "kar" : 0,]);
			}
			else	m_gift = Last_level_up["c"][lvl];
		}
	}
	else if( lvl<160 )
	{
		if( undefinedp(Last_level_up["d"]) )
		{
			newf = 1;
			Last_level_up["d"] = ([ lvl : ([ "str" : 0,"cor" : 0,"int" : 0,"spi" : 0,"cps" : 0, "per" : 0, "con" : 0, "kar" : 0,]),]);	
		}
		else
		{
			if( undefinedp(Last_level_up["d"][lvl]) )
			{
				newf = 1;
				Last_level_up["d"][lvl] = ([ "str" : 0,"cor" : 0,"int" : 0,"spi" : 0,"cps" : 0, "per" : 0, "con" : 0, "kar" : 0,]);
			}
			else	m_gift = Last_level_up["d"][lvl];
		}
	}
	else
	{
		if( undefinedp(Last_level_up["e"]) )
		{
			newf = 1;
			Last_level_up["e"] = ([ lvl : ([ "str" : 0,"cor" : 0,"int" : 0,"spi" : 0,"cps" : 0, "per" : 0, "con" : 0, "kar" : 0,]),]);	
		}
		else
		{
			if( undefinedp(Last_level_up["e"][lvl]) )
			{
				newf = 1;
				Last_level_up["e"][lvl] = ([ "str" : 0,"cor" : 0,"int" : 0,"spi" : 0,"cps" : 0, "per" : 0, "con" : 0, "kar" : 0,]);
			}
			else	m_gift = Last_level_up["e"][lvl];
		}
	}
	if( newf!=1 )
	{
		gifts = keys(m_gift);
		if( gifts && arrayp(gifts) && sizeof(gifts)>0 )
		{
			for(i=0;i<sizeof(gifts);i++)
			{
				if( m_gift[gifts[i]]>0 )
				{
					me->add(gifts[i],m_gift[gifts[i]]);
					if( !undefinedp(prop[gifts[i]]) )
						tell_object(this_object(),HIY"【系统】你的〖 "HIG+prop[gifts[i]]+HIY" 〗增加了 "HIR+(m_gift[gifts[i]])+HIY" 点。\n"NOR);
				}
			}
			maxgin = this_object()->query("max_gin");
			effgin = this_object()->query("eff_gin");
			gin = this_object()->query("gin");
			gin = effgin-gin;
			effgin = maxgin-effgin;
			me->add("max_gin",10);
			me->set("eff_gin",me->query("max_gin"));
			me->set("gin",me->query("eff_gin")-gin);
			tell_object(this_object(),HIY"【系统】你的〖 "HIG"活力"HIY" 〗增加了 "HIR+10+HIY" 点。\n"NOR);
			return 1;
		}
	}	
	
	m_gift= ([
		"将军府"	: ({1,1,1,1,1,0,2,0,}),
		"月宫"		: ({1,1,1,2,1,0,1,0,}),
		"南海普陀山"	: ({1,1,1,2,2,0,1,0,}),
		"阎罗地府"	: ({1,1,1,1,2,0,1,0,}),
		"方寸山三星洞"  : ({2,1,1,1,1,0,2,0,}),
		"大雪山"	: ({1,2,1,1,2,0,1,0,}),
		"五庄观"	: ({1,1,2,2,1,0,1,0,}),
		"龙宫"		: ({2,2,1,1,1,0,1,0,}),
		"火云洞"	: ({2,1,2,1,1,0,1,0,}),
		"陷空山无底洞"	: ({2,2,1,1,1,0,1,0,}),
		"蜀山派"	: ({1,2,1,1,1,0,2,0,}),
		"盘丝洞"	: ({1,1,2,1,1,0,1,0,}),
		"百花谷"	: ({1,1,1,1,2,0,1,0,}),
		"散仙派"	: ({1,1,1,2,2,0,1,0,}),
		"百姓"		: ({1,1,1,1,1,0,1,0,}),
	]);
	if( !fam=me->query("family/family_name") )
		rewards = m_gift["百姓"];
	else if( undefinedp(m_gift[fam]) )
		rewards = m_gift["百姓"];
	else	rewards = m_gift[fam];
	
	for(i=0;i<sizeof(gifts);i++)
	{
		if( rewards[i]*v>0 )
		{
			k = random(rewards[i]*v+1);
			if( k>0 )
			{
				me->add(gifts[i],k);
				if( lvl<40 )
					Last_level_up["a"][lvl][gifts[i]]+=k;
				else if( lvl<80 )
					Last_level_up["b"][lvl][gifts[i]]+=k;
				else if( lvl<120 )
					Last_level_up["c"][lvl][gifts[i]]+=k;
				else if( lvl<160 )
					Last_level_up["d"][lvl][gifts[i]]+=k;
				else	Last_level_up["e"][lvl][gifts[i]]+=k;
				tell_object(this_object(),HIY"【系统】你的〖 "HIG+prop[gifts[i]]+HIY" 〗增加了 "HIR+(k)+HIY" 点。\n"NOR);
			}	
		}	
	}
	
	maxgin = this_object()->query("max_gin");
	effgin = this_object()->query("eff_gin");
	gin = this_object()->query("gin");
	gin = effgin-gin;
	effgin = maxgin-effgin;
	me->add("max_gin",10);
	me->set("eff_gin",me->query("max_gin"));
	me->set("gin",me->query("eff_gin")-gin);
	tell_object(this_object(),HIY"【系统】你的〖 "HIG"活力"HIY" 〗增加了 "HIR+10+HIY" 点。\n"NOR);
	if( !fam=me->query("family/family_name") )
		return 1;
	if( fam=="月宫" || fam=="百花谷" || fam=="盘丝洞" )
	{
		if( me->query_level()%3==0 )
		{
			me->add("per",1);
			if( lvl<40 )
				Last_level_up["a"][lvl]["per"]+=1;
			else if( lvl<80 )
				Last_level_up["b"][lvl]["per"]+=1;
			else if( lvl<120 )
				Last_level_up["c"][lvl]["per"]+=1;
			else if( lvl<160 )
				Last_level_up["d"][lvl]["per"]+=1;
			else	Last_level_up["e"][lvl]["per"]+=1;
			tell_object(this_object(),HIY"【系统】你的〖 "HIG+"魅力"+HIY" 〗增加了 "HIR+"1"+HIY" 点。\n"NOR);
		}
	}
	else if( fam=="将军府" || fam=="散仙派" )
	{
		if( me->query_level()%4==0 )
		{
			me->add("kar",1);
			if( lvl<40 )
				Last_level_up["a"][lvl]["kar"]+=1;
			else if( lvl<80 )
				Last_level_up["b"][lvl]["kar"]+=1;
			else if( lvl<120 )
				Last_level_up["c"][lvl]["kar"]+=1;
			else if( lvl<160 )
				Last_level_up["d"][lvl]["kar"]+=1;
			else	Last_level_up["e"][lvl]["kar"]+=1;
			tell_object(this_object(),HIY"【系统】你的〖 "HIG+"福缘"+HIY" 〗增加了 "HIR+"1"+HIY" 点。\n"NOR);
		}
	}
	else
	{
		if( me->query_level()%6==0 && random(5)==3 )
		{
			me->add("kar",1);
			if( lvl<40 )
				Last_level_up["a"][lvl]["kar"]+=1;
			else if( lvl<80 )
				Last_level_up["b"][lvl]["kar"]+=1;
			else if( lvl<120 )
				Last_level_up["c"][lvl]["kar"]+=1;
			else if( lvl<160 )
				Last_level_up["d"][lvl]["kar"]+=1;
			else	Last_level_up["e"][lvl]["kar"]+=1;
			tell_object(this_object(),HIY"【系统】你的〖 "HIG+"福缘"+HIY" 〗增加了 "HIR+"1"+HIY" 点。\n"NOR);
		}
	}
	return 1;
}

// override add function
mixed add(string prop, mixed data)
{
	int max,lvl,n,old;
	string para;
	mapping check = ([
		"combat_exp" 	: "武学经验",
		"potential"	: "潜能",
		"daoxing"	: "道行",
	]);
	
	if( data && member_array(prop,keys(check))!=-1 )
	{
		old = (int)query(prop,1);
		n = old+(int)data;
		if( (n<0 || old>=2100000000) && (int)data>0 )
		{
			tell_object(this_object(),HIR"【系统】你的 "HIY+check[prop]+HIR" 数据濒临溢出边缘，将不再增加。\n"NOR);
			return 0;
		}
		switch(prop)
		{
			case "potential" :
				if( (int)data>0 )
				{
					if( ((int)this_object()->query("potential")-(int)this_object()->query("learned_points")+(int)data)>=this_object()->query_level()*5000 )
					{
						n = this_object()->query_level()*5000+(int)this_object()->query("learned_points");
						this_object()->set("potential",n);
                                                if( time()>this_object()->query("channel/last_warr")+600 )
                                                {
                                                        tell_object(this_object(),HIY"【系统】你的人物等级只支持"HIR+this_object()->query_level()*5000+HIY"潜能，赶紧去完成任务升级吧。\n"NOR);
                                                        this_object()->set("channel/last_warr",time());
                                                }
						return 0;					
					}
				}	
				break;	
			case "combat_exp" :
				if( (int)data>0 )
				{
					if( last_num(this_object()->query_level())==9 && n>=this_object()->query_max_exp() )
					{
                                                 if( time()>this_object()->query("channel/last_warr")+600 )
                                                {
                                                        tell_object(this_object(),HIY"【系统】你的武学修为已到瓶颈，赶紧去完成"HIY+"〖"HIR+chinese_number(this_object()->query_level()+1)+"级突破任务"HIY"〗吧。\n"NOR);
                                                        this_object()->set("channel/last_warr",time());
                                                }
						return 0;					
					}
					lvl = this_object()->query_level();
					max = this_object()->query_max_exp();
					old = (int)this_object()->query(prop,1);
					old+= (int)data;
					if( old>=max )
					{
						if( this_object()->level_up() )
						{
							tell_object(this_object(),HIG"【系统】你的等级提升了"HIR"1"HIG"级。\n"NOR);
							CHAR_D->setup_char( this_object() );
							UPDATE_D->check_user(this_object(),1);
							this_object()->powerup(0,1);
							this_object()->set_temp("login_data/time", time());
							this_object()->set_temp("login_data/exp", 0);
							this_object()->save(1);
							return n;
						}
						else	tell_object(this_object(),HIR"【系统】等级升级失败。\n"NOR);
					}
				}		
				break;
			case "daoxing" :
				if( (int)data>0 )
				{
					max = this_object()->query_max_daoxing();
					if( this_object()->query("daoxing")>=max )
					{		
						this_object()->set("daoxing",max);
						if( time()>this_object()->query("channel/last_warr")+600 )
                                                {
                                                        tell_object(this_object(),HIG"【系统】你当前的等级只支持"HIG+COMBAT_D->chinese_daoxing(max)+"道行"HIG"。\n"NOR);
                                                        this_object()->set("channel/last_warr",time());
                                                }
						return 0;
					}
				}	
				break;
		}
	}	
	return ::add(prop, data);
}

mixed doing_job(string type)
{
	mapping now_j;
	if( !xy_job || !mapp(xy_job) || !type )
		return 0;
	if( undefinedp(xy_job[type]) )
		return 0;
	now_j = xy_job[type];
	if( undefinedp(now_j["doing"]) ) 
		return 0;
	if( now_j["doing"]==0 )
		return 0;
	if( undefinedp(now_j["msg"]) )
		return 1; 
	return now_j["msg"];		
}

int set_job_level(string type,int level)
{
	string *types = ({
		"李靖任务","解密任务","门派任务","袁天罡任务","如来任务","送信任务","寻宝任务","分配任务","押镖任务","守城任务","杀手任务",
	});	
	
	if( !type || member_array(type,types)==-1 )
		return 0;
	if( !xy_job_level || !mapp(xy_job_level) )
		xy_job_level = ([]);
	if( level<0 )
		level = 0;
	xy_job_level[type] = level;
	return level;
}			

mixed get_job(string type,mixed jobs)
{
	mapping now_j;
	string target_id,target_name,msg;
	object target;
	int succ,fail,level;
	string *types = ({
		"李靖任务","解密任务","门派任务","袁天罡任务","如来任务","送信任务","寻宝任务","分配任务","押镖任务","守城任务","杀手任务",
	});	
	
	if( !type || member_array(type,types)==-1 )
		return "任务获取错误，不可识别的job_type";
	if( !jobs )
		return "任务获取错误，不可识别的job参数";	
	if( !xy_job || !mapp(xy_job) )
		xy_job = ([]);	
	if( !undefinedp(xy_job[type]) )
	{
		if( doing_job(type) )
			return "你已接了这个任务，请完成或者去任务发布者处取消此任务。\n*注：取消任务将会消耗你 1点活力。\n";
	}				 
	if( this_object()->query("gin")<1 )
		return "你的活力不够了。";
	if( arrayp(jobs) )
	{
		if( sizeof(jobs)<3 )
			return "任务获取错误，数量不足的job_array";
		target_id = jobs[1];
		target_name = jobs[0];
		msg = jobs[2];
		if( sizeof(jobs)>3 )
			target = jobs[3];
		else	target = 0;
	}
	else if( mapp(jobs) )
	{
		if( undefinedp(jobs["target_name"]) )
			return "任务获取错误，不可识别的对象name";
		if( undefinedp(jobs["target_id"]) )
			return "任务获取错误，不可识别的对象id";
		if( undefinedp(jobs["msg"]) )
			return "任务获取错误，不可识别的job_msg";
		target_id = jobs["target_id"];
		target_name = jobs["target_name"];
		msg = jobs["msg"];
		if( undefinedp(jobs["target"]) ) 
			target = 0;
		else	target = jobs["target"];
	}
	else	return "任务获取错误，不可识别的job_jobs";
	
	succ = fail = 0;
	if( undefinedp(xy_job[type]) )
		now_j = ([]);
	else
	{
		now_j = xy_job[type];
		if( !now_j || !mapp(now_j) )
			now_j = ([]);
	}
	if( !undefinedp(now_j["succ"]) )
		succ+= now_j["succ"];
	if( !undefinedp(now_j["fail"]) )
		fail+= now_j["fail"];
		
	now_j["doing"] = 1;	
	now_j["target_id"] = target_id;
	now_j["target_name"] = target_name;
	now_j["target"] = target;
	now_j["msg"] = msg;
	now_j["succ"] = succ;
	now_j["fail"] = fail;
	xy_job[type] = now_j;
	return msg;
}

mixed cancel_job(string type)
{
	object guai;
	int fail;
	mapping now_j;
	string *types = ({
		"李靖任务","解密任务","门派任务","袁天罡任务","如来任务","送信任务","寻宝任务","分配任务","押镖任务","守城任务","杀手任务",
	});	
	
	if( !type || member_array(type,types)==-1 )
		return "任务获取错误，不可识别的job_type";
	if( undefinedp(xy_job[type]) )
		return "你有做这个任务吗？";
	if( !doing_job(type) )
		return "你有做这个任务吗？";			
	if( !this_object()->query_temp("job_cancel_warr") )
	{
		this_object()->set_temp("job_cancel_warr",1);
		return "取消任务将消耗1点活力，如果你确定要取消，那就重新提交一次。";
	}
	if( this_object()->query("gin")<1 )
		return "你的活力不够。";
	this_object()->add("gin",-1);	
	now_j = xy_job[type];
	if( !undefinedp(now_j["fail"]) )
		fail = now_j["fail"]+1;
	else	fail = 1;
	now_j["doing"] = 0;	
	now_j["target_id"] = 0;
	now_j["target_name"] = 0;
	if( !undefinedp(now_j["target"]) )
	{
		guai = now_j["target"];
		if( guai )
		{
			if( environment(guai) )
			{
				guai->remove_all_killer();
				all_inventory(environment(guai))->remove_killer(guai);
				message("vision",guai->name()+"急急忙忙的离开了。\n",environment(guai));
			}
			else if( !interactive(guai) ) destruct(guai);
		}	
	}
	now_j["target"] = 0;
	now_j["msg"] = 0;
	now_j["fail"] = fail;
	now_j["exp"] = 0;
	now_j["daoxing"] = 0;
	now_j["pot"] = 0;
	now_j["gold"] = 0;
	xy_job[type] = now_j;
	set_job_level(type,0);	
	return "你真是没用，便再给你一次机会吧！";
}

int query_job_level(string type)
{
	string *types = ({
		"李靖任务","解密任务","门派任务","袁天罡任务","如来任务","送信任务","寻宝任务","分配任务","押镖任务","守城任务","杀手任务",
	});	
	if( !type || member_array(type,types)==-1 )
		return 0;
	if( !xy_job_level || !mapp(xy_job_level) )
		return 0;
	if( undefinedp(xy_job_level[type]) )
		return 0;	
	return xy_job_level[type];	
}

mixed finish_job(string type,int *prop)
{
	int succ,exp,pot,dx,gold,level;
	mapping now_j;
	string *types = ({
		"李靖任务","解密任务","门派任务","袁天罡任务","如来任务","送信任务","寻宝任务","分配任务","押镖任务","守城任务","杀手任务",
	});	
	if( !type || member_array(type,types)==-1 )
		return "完成任务进程错误，不可识别的job_type";
	if( !prop || !arrayp(prop) || sizeof(prop)<1 )
		return "完成任务进程错误，不可识别的奖励阵列";		
	if( undefinedp(xy_job[type]) )
		return "完成任务进程错误：无任务标志";
	if( !doing_job(type) )
		return "完成任务进程错误：非进行状态";			
	now_j = xy_job[type];
	if( !undefinedp(now_j["succ"]) )
		succ = now_j["succ"]+1;
	else	succ = 1;
	exp = pot = dx = gold = 0;
	if( sizeof(prop)==4 )
	{
		exp = prop[0];
		dx = prop[1];
		pot = prop[2];
		gold = prop[3];
	}
	if( sizeof(prop)==3 )
	{
		exp = prop[0];
		dx = prop[1];
		pot = prop[2];
	}
	if( sizeof(prop)==2 )
	{
		exp = prop[0];
		dx = prop[1];
	}
	else	exp = prop[0];
	now_j["doing"] = 0;	
	now_j["target_id"] = 0;
	now_j["target_name"] = 0;
	now_j["target"] = 0;
	now_j["msg"] = 0;
	now_j["succ"] = succ;
	now_j["exp"] = exp;
	now_j["daoxing"] = dx;
	now_j["pot"] = pot;
	now_j["gold"] = gold;
	xy_job[type] = now_j;
	this_object()->save();
	return "你完成了一个"+type;	
}

mapping query_xy_job()
{
	return xy_job;
}

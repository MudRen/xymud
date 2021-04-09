#include <ansi.h> 
#include <combat.h> 
inherit SUPER_NPC;

int is_maze(){return 1;}

mapping Wuxing = ([
	"辰" : 1,
	"戌" : 1,
	"丑" : -1,
	"未" : -1,
	"己" : -1,
]);

mapping Wuxing2 = ([
	"石狮" : "辰",
	"山犼" : "戌",
	"山鬼" : "丑",
	"山魈" : "未",
	"豬魔" : "己",
	"鬼车" : "辰",
]);

mapping My_level = ([
	"石狮" : 1,
	"山犼" : 2,
	"山鬼" : 3,
	"山魈" : 4,
	"豬魔" : 5,
	"鬼车" : 6,
	"流连" : 7,
]);

mapping My_level2 = ([
	1 : ({"石狮","shi shi",}),
	2 : ({"山犼","shan hou",}),
	3 : ({"山鬼","shan gui",}),
	4 : ({"山魈","shan xiao"}),
	5 : ({"豬魔","zhu mo",}),
	6 : ({"鬼车","gui che",}),
	7 : ({"流连","liu lian"}),
]);

mapping Name = ([
	"极荒" : "辰",
	"望川" : "戌",
	"开山" : "丑",
	"守阵" : "未",
	"中州" : "己",
]);	

string *Names = ({
	"土蜘蛛","tu zhizhu","土妖","tu yao","黄怪","huang guai",
});	

nosave int my_wx = 0;
nosave int lvl = 0;

void remove_all()
{
	object *inv;
	int i;
	delete("title");
	delete("my_type");
	delete("my_level");
	lvl = 0;
	inv = all_inventory();
	if( !inv || sizeof(inv)<1 )
		return;
	for(i=0;i<sizeof(inv);i++)
		destruct(inv[i]);	
}

void init_texing()
{
	string str,*texing;
	delete("title");
	if( lvl<=3 )
		texing = ({
			"","","","",HIB"驭法"NOR,"","",HIR"彪悍"NOR,HIM"通灵"NOR,RED"吸血"NOR,
			CYN"偷心"NOR,HIY"反戈"NOR,HIW"登峰"NOR,HIC"震古"NOR,MAG"死锋"NOR,BLU"死毒"NOR,HIM"死幻"NOR,
			"","","","","","","","","","","","",
		});
	else if( lvl<5 )
		texing = ({
			"","","",YEL"厚土"NOR,HIB"驭法"NOR,"",HIG"轻灵"NOR,HIR"彪悍"NOR,HIM"通灵"NOR,RED"吸血"NOR,
			CYN"偷心"NOR,HIY"反戈"NOR,HIW"登峰"NOR,HIC"震古"NOR,MAG"死锋"NOR,BLU"死毒"NOR,HIM"死幻"NOR,
			"","","","","","","","",
		});
	else	texing = ({
			YEL"厚土"NOR,HIB"驭法"NOR,HIG"轻灵"NOR,HIR"彪悍"NOR,HIM"通灵"NOR,RED"吸血"NOR,
			CYN"偷心"NOR,HIY"反戈"NOR,HIW"登峰"NOR,HIC"震古"NOR,MAG"死锋"NOR,BLU"死毒"NOR,HIM"死幻"NOR,
	});
	str = texing[random(sizeof(texing))];
	if( str!="" )
	{
		set("my_type",str);
		set("title",HIC"精英"NOR);
		str = COLOR_D->clean_color(str);
		switch(str)
		{
			case "反戈" : //受到伤害的10%反弹
				add_temp("apply/re_spells_effdamage",10);
				add_temp("apply/re_combat_effdamage",10);
				add_temp("apply/re_spells_damage",10);
				add_temp("apply/re_combat_damage",10);
				break;
			case "登峰" : //物理命中提高100%
				add_temp("apply/combat_succ",100);
				break;
			case "震古" : //法术命中提高100%
				add_temp("apply/spells_succ",100);
				break;
			case "彪悍" : 
				add_temp("apply/combat_damage",1000);
				break;	
			case "通灵" : 
				add_temp("apply/spells_damage",1000);
				break;	
		}
		add("max_kee",3000);
		add("max_sen",3000);	
	}
	else	
	{
		add("max_kee",10000);
		add("max_sen",10000);
	}
}

void set_skills(){}

varargs void init_name(int v)
{
	string name,*id,*tmp,nn;
	int i;
	
	if( v>0 && v<8 )
	{
		name = My_level2[v][0];
		id = ({My_level2[v][1],"gui guai","guai","mo",}); 
		lvl = v;
	}
	else
	{
		i = random(sizeof(Names)/2)*2;
		name = Names[i];
		id = ({Names[i+1],"gui guai","guai","mo",});
	}
	if( !undefinedp(Wuxing2[name]) )
	{
		nn = Wuxing2[name];
		if( !undefinedp(Wuxing[nn]) )
			my_wx+= Wuxing[nn];
	}
	if( !undefinedp(My_level[name]) )
	{
		lvl = My_level[name];
		set("my_level",lvl);
	}
	tmp = keys(Name);
	nn = tmp[random(sizeof(tmp))];
	name = nn+name;
	set_name(name,id);
	nn = Name[nn];
	if( !undefinedp(Wuxing[nn]) )
		my_wx+= Wuxing[nn];
	set_skills();	
	set("force_factor",this_object()->query_skill("force")/5);
	set("mana_factor",this_object()->query_skill("spells")/3);	
}	

string short()
{
        string str = ::short();
        if( !query("my_type") )
                return str;
        return str+NOR"["+query("my_type")+NOR"]";
}

string long()
{
	string str,long = "终南山土极之地「"YEL"终南幽谷"NOR"」之中的怪物。\n";
	if( !stringp(str=query("my_type")) 
	 || strlen(str)<2 )
	 	return long;
	str = COLOR_D->clean_color(str);	
	switch(str)	
	{
		case "厚土" : long+= HIC"怪物特效：物理免疫。\n"NOR;break;
		case "驭法" : long+= HIC"怪物特效：法术免疫。\n"NOR;break;
		case "轻灵" : long+= HIC"怪物特效：busy状态下伤害降低。\n"NOR;break;
		case "彪悍" : long+= HIC"怪物特效：物理伤害提高100%。\n"NOR;break;
		case "通灵" : long+= HIC"怪物特效：法术伤害提高100%。\n"NOR;break;
		case "吸血" : long+= HIC"怪物特效：击中回复自己1%的气血值。\n"NOR;break;
		case "偷心" : long+= HIC"怪物特效：击中回复自己2%的法力值。\n"NOR;break;
		case "反戈" : long+= HIC"怪物特效：受到伤害的10%反弹给攻击者。\n"NOR;break;
		case "登峰" : long+= HIC"怪物特效：物理命中提高100%。\n"NOR;break;
		case "震古" : long+= HIC"怪物特效：法术命中提高100%。\n"NOR;break;
		case "死锋" : long+= HIC"怪物特效：死亡时释放物理伤害。\n"NOR;break;
		case "死毒" : long+= HIC"怪物特效：死亡时释放毒伤害。\n"NOR;break;
		case "死幻" : long+= HIC"怪物特效：死亡时释放混乱伤害。\n"NOR;break;
	}
	return long;	
}

void create()
{
        init_name();
        set("age",17+random(20));
        set("WX",my_wx);
        setup();
}

string obj_name(object ob)
{
        string str;
        if( !ob )
                return "";
        str = ob->name(1);
        str = COLOR_D->clean_color(str);
        return str;
}

void hurt_env(string type)
{
	object *inv;
	int i,damage;
	if( !environment() )
		return;
	inv = all_inventory(environment());
	if( !inv || sizeof(inv)<1 )
		return;
	for(i=0;i<sizeof(inv);i++)
	{
		if( inv[i]->is_maze() )
			continue;
		if( !inv[i]->is_character() )
			continue;
		switch(type)
		{
			case "combat" : 
				damage = this_object()->query_combat_damage();
				damage = inv[i]->receive_wound("kee",damage,this_object(),TYPE_PERFORM);
				if( damage>0 )
					message_vision(HIR"结果对$N"HIR"造成了"HIY+damage+HIR"点物理伤害！\n"NOR,inv[i]);
				break;
			case "du" : 
				damage = 5+random(15);
				inv[i]->apply_condition("wuxing",(int)inv[i]->query_condition("wuxing")+damage);
				message_vision(HIR"结果对$N"HIR"造成了"HIY+damage+HIR"秒五行奇毒伤害！\n"NOR,inv[i]);	
				break;
			case "hl" :
				damage = 3+random(5);
				inv[i]->start_hunluan((int)inv[i]->is_hunluan()+damage,"你只觉眼前金光闪闪，一时不知干啥好。\n");
				message_vision(HIR"结果对$N"HIR"造成了"HIY+damage+HIR"秒混乱伤害！\n"NOR,inv[i]);	
				break;
		}			
	}	
}

void reward_ob(object who)
{
        object ob,xin,weapon;
        int i,succ;
        string *dir,str,file,arg="";

        message_vision (YEL"\n$N"YEL"浑身发出一阵怪声，片刻间就碎成了一堆土石。\n"NOR,this_object());
        if( stringp(str=query("my_type")) && strlen(str)>2 )
	{	
		str = COLOR_D->clean_color(str);
		switch(str)
		{
			case "死锋" : hurt_env("combat");break;
			case "死毒" : hurt_env("du");break;
			case "死幻" : hurt_env("hl");break;
        	}
        }
        
        if( !who || !userp(who) || !present(who,environment()) )
        {
                destruct(this_object());
                return;
        }
        
        succ = who->query_kar();        
        if( random(succ)>10 )
        {
                file = ("/d/maze/tupo40-5/obj/xiu");
                ob = new(file);
                ob->set("owner_id",who->query("id"));
                if( !ob->move(who) )
                {
                        destruct(ob);
                        tell_object(who,HIR"【副本】终南幽谷：你的背包满了。\n"NOR);
                }
                else    
                {
                        tell_object(who,HIY"【副本】终南幽谷：你得到了 "HIG+obj_name(ob)+HIY" 。\n"NOR);
                        arg+= obj_name(ob);
                }
        }
        if( random(succ)>10 )
        {
	        i = random(2)+1;
        	while(i--)
        	{
        		if( random(2) )
	        	{
        	        	ob = new("/d/maze/tupo40-5/obj/armor_sj");
                		if( strsrch(arg,"厚土石")==-1 )
                			arg+= "、厚土石";
                	}
                	else
                	{
                		ob = new("/d/maze/tupo40-5/obj/weapon_sj");
				if( strsrch(arg,"金芒石")==-1 )
                			arg+= "、金芒石";                			
                	}
                        ob->set("owner_id",who->query("id"));
                	if( !ob->move(who) )
                	{
                        	destruct(ob);
                        	tell_object(who,HIR"【副本】终南幽谷：你的背包满了。\n"NOR);
	                }
        	        else    tell_object(who,HIY"【副本】终南幽谷：你得到了 "HIG+obj_name(ob)+HIY" 。\n"NOR);
               } 
        }
        
        if( query("my_level")==7 )
        {
        	succ = 100;
        	dir = ({"max",});
        }
        else if( query("my_level")==6 )
        {
        	succ = 50;
        	if( my_wx>=0 )
        		dir = ({"yang6","yang6","yang6","yang6","yang5","max",});
        	else	dir = ({"yin6","yin6","yin6","yin6","yin5","max",});	
        }
        else if( query("my_level")==5 )
        {
        	succ = random(100);
        	if( my_wx>=0 )
        		dir = ({"yang5","yang5","yang5","yang5","yang4","yang6",});
        	else	dir = ({"yin5","yin5","yin5","yin5","yin6","yin4",});	
        }	
        else if( query("my_level")==4 )
        {
        	succ = random(50);
        	if( my_wx>=0 )
        		dir = ({"yang4","yang4","yang4","yang4","yang3","yang5",});
        	else	dir = ({"yin4","yin4","yin4","yin4","yin5","yin3",});	
        }	
        else if( query("my_level")==3 )
        {
        	succ = random(25);
        	if( my_wx>=0 )
        		dir = ({"yang3","yang3","yang3","yang3","yang2","yang4",});
        	else	dir = ({"yin3","yin3","yin3","yin3","yin4","yin2",});	
        }	
        else if( query("my_level")==2 )
        {
        	succ = random(15);
        	if( my_wx>=0 )
        		dir = ({"yang2","yang2","yang2","yang2","yang1","yang3",});
        	else	dir = ({"yin2","yin2","yin2","yin2","yin3","yin1",});	
        }
        else
        {
        	succ = random(10);
        	if( my_wx>=0 )
        		dir = ({"yang1","yang1","yang1","yang1","yang2",});
        	else	dir = ({"yin1","yin1","yin1","yin1","yin2",});	
        }
        
        if( random(succ)>5 || query("my_level")>5 )
        {
        	ob = new("/d/maze/tupo40-5/obj/"+dir[random(sizeof(dir))]);
        	if( !ob->move(who) )
		{
        		destruct(ob);
                	tell_object(who,HIR"【副本】终南幽谷：你的背包满了。\n"NOR);
		}
        	else    tell_object(who,HIY"【副本】终南幽谷：你得到了 "HIG+obj_name(ob)+HIY" 。\n"NOR);
        	arg+= "、"+obj_name(ob);
        	who->set("mark/40tupo",1);
        }
        if( strlen(arg)>6 && (random(query("my_level"))>3||query("my_level")>6) )       
        	CHANNEL_D->do_channel(this_object(),"rumor","听说"+who->name()+HIM"在终南山"NOR YEL"终南幽谷"NOR HIM"得到了"+arg+"。"NOR);
        destruct(this_object());        
        return;
}

int accept_fight(object who){return 0;}

void kill_ob(object who)
{
        if( !this_object()->is_fihgting() )
        {
                powerup(0,1);
                stop_busy(100);
        }
        ::kill_ob(who);
}

int is_pet(){return 1;}

varargs int receive_wound(string type, int damage, object who,mixed attack_type)
{
	string str;
	if( !stringp(str=query("my_type")) 
	 || strlen(str)<2 )
		return ::receive_wound(type,damage,who,attack_type);
        if( who && who!=this_object() )
        {
        	str = COLOR_D->clean_color(str);
        	if( str=="厚土" && attack_type!=TYPE_CAST )
        		damage = 0;
        	else if( str=="驭法" && attack_type==TYPE_CAST )
        		damage = 0;
        	else if( str=="轻灵" && this_object()->is_busy() )
        		damage = 0;
        }               
        return ::receive_wound(type,damage,who,attack_type);
}

varargs int receive_damage(string type, int damage, object who,mixed attack_type)
{
	string str;
	if( !stringp(str=query("my_type")) 
	 || strlen(str)<2 )
		return ::receive_damage(type,damage,who,attack_type);
        if( who && who!=this_object() )
        {
        	str = COLOR_D->clean_color(str);
        	if( str=="厚土" && attack_type!=TYPE_CAST )
        		damage = 0;
        	else if( str=="驭法" && attack_type==TYPE_CAST )
        		damage = 0;
        	else if( str=="轻灵" && this_object()->is_busy() )
        		damage = 0;
        }               
        return ::receive_damage(type,damage,who,attack_type);
}

mixed hit_ob(object me, object who,int damage,mixed attack_type)
{
	string str;
	if( !stringp(str=query("my_type")) 
	 || strlen(str)<2 )
		return 0;
	if( !living(me) || !who || !me->is_fighting(who) || damage<=0 )
		return 0;
	str = COLOR_D->clean_color(str);	
	switch(str)
	{
		case "彪悍" : //物理伤害提高100%
			if( attack_type!=TYPE_CAST )
				return damage;
			break;	
		case "通灵" : //法术伤害提高100%
			if( attack_type==TYPE_CAST )
				return damage;
			break;	
		case "吸血" : //击中回复自己1%的气血值
			me->receive_heal("kee",me->query_maxkee()/100+1);
			me->receive_curing("kee",me->query_maxkee()/100+1);
			return RED"$N"RED"开始疯狂的吸血！\n"NOR;
		case "偷心" : //击中回复自己2%的法力值
			if( me->query("mana")<me->query_maxmana()*2 )
			{
				me->add("mana",me->query_maxmana()/50+1);
				return HIC"$N"HIC"只觉得自己的法力越来越充沛了。\n"NOR;
			}
			break;
	}
	return 0;		
}

void init()
{
	add_action("do_go","go");
}

int do_go(string arg)
{
	if( userp(this_player()) )
		return err_msg(name()+"龇牙咧嘴的拉住了你。\n");
	return 0;
}	

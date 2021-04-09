#include <ansi.h>
inherit NPC;
inherit F_SAVE;

#define NONE 0		//比赛状态 无
#define INVITE 1	//比赛状态 邀请等待 
#define FIGHT 3		//比赛状态 比赛中
#define DONE 7		//比赛状态 结束
#define DELAY 10	//比赛状态 等待	

#define MAXROUND 3	//每级最大轮数
//#define ROUND_TIME 1200 //每轮20分钟
#define ROUND_TIME 120 //TEST TIME
#define LEVEL_TIME 4000 //每级别时间

int Now_level=0;	//目前的级别  40.50.60.70.80.90.100.110.120.130.140.150,150以上将不能参加
int round=1; 	//当前轮数
nosave int can_save=1;		//能否存盘 1.能，0.否
nosave int Status = 0;		//目前的比赛状态
nosave mapping Player = ([]);	//目前参加的玩家 id:OBJ
nosave string *Wins;		//
nosave string title;		//
nosave mapping Rewards = ([	//奖品
	40 : ({ "gold-1","gold-5","gold-10","xin-dx1","xin-exp1","xin-pot1",
		"yuan-dx1","yuan-exp1","yuan-pot1","mp-dx1","mp-pot1","mp-exp1",
		"lvl-40",
	}),
	50 : ({ "gold-5","gold-10","xin-dx1","xin-exp1","xin-pot1",
		"yuan-dx1","yuan-exp1","yuan-pot1","mp-dx1","mp-pot1","mp-exp1",
		"yuan-dx2","yuan-exp2","yuan-pot2","lvl-50",
	}),
	60 : ({ "gold-5","gold-10",
		"yuan-dx2","yuan-exp2","yuan-pot2","mp-dx2","mp-pot2","mp-exp2",
		"lvl-60",
	}),
	70 : ({ "gold-5","gold-10",
		"yuan-dx2","yuan-exp3","yuan-pot3","mp-dx3","mp-pot3","mp-exp3",
		"yuan-dx3","yuan-exp2","yuan-pot2","mp-dx2","mp-pot2","mp-exp2",
		"lvl-70",
	}),
	80 : ({ "gold-50","gold-10",
		"li-dx1","li-exp1","li-pot1","mp-dx3","mp-pot3","mp-exp3",
		"lvl-80",
	}),
	90 : ({ "gold-50","gold-100",
		"li-dx1","li-exp1","li-pot1","mp-dx3","mp-pot3","mp-exp3",
		"li-dx2","li-exp2","li-pot2",
		"lvl-90",
	}),
	100 : ({ "gold-50","gold-100",
		"li-dx2","li-exp2","li-pot2","mp-dx3","mp-pot3","mp-exp3",
	}),
	110 : ({ "gold-50","gold-100","li-dx3","li-exp3","li-pot3",
		"li-dx2","li-exp2","li-pot2","mp-dx3","mp-pot3","mp-exp3",
	}),
	120 : ({ "gold-50","gold-100","li-dx3","li-exp3","li-pot3",
		"mp-dx3","mp-pot3","mp-exp3",
	}),
	130 : ({ "gold-50","gold-100","li-dx3","li-exp3","li-pot3",
		"mp-dx3","mp-pot3","mp-exp3",
	}),
	140 : ({ "gold-50","gold-100","li-dx3","li-exp3","li-pot3",
		"mp-dx3","mp-pot3","mp-exp3",
	}),
	150: ({ "gold-50","gold-100","li-dx3","li-exp3","li-pot3",
		"mp-dx3","mp-pot3","mp-exp3",
	}),
]);

void reset_init();
void set_status (int i) { Status = i; }

string check_title()
{
        string str;
        if( Now_level<=0 )
        	return 0;
        str = sprintf(" %s级别以下妖魔大会 ",chinese_number(Now_level));
        return str;
}

mapping query_players(){ return Player;}
void remove_player(string nameid) { map_delete(Player,nameid);}

int check_palyer_level(object who)
{
	if( !who )
		return 0;
	if( !environment() || base_name(environment())!="/d/kaifeng/yuwang5" )
		return 0;
	if( who->query_level()>=150 )
		return -1;
	if( who->query_level()<30 )
		return -2;			
	//40.50.60.70.80.90.100.110.120.130.140.150
	if( who->query_level()<40 )
		return 40;
	else if( who->query_level()<50 )
		return 50;
	else if( who->query_level()<60 )
		return 60;
	else if( who->query_level()<70 )
		return 70;
	else if( who->query_level()<80 )
		return 80;
	else if( who->query_level()<90 )
		return 90;
	else if( who->query_level()<100 )
		return 100;
	else if( who->query_level()<110 )
		return 110;
	else if( who->query_level()<120 )
		return 120;
	else if( who->query_level()<130 )
		return 130;
	else if( who->query_level()<140 )
		return 140;
	else	return 150;
}

void announce (string str)
{
	if( environment() )
        {
          	delete("channel");
                CHANNEL_D->do_channel(this_object(),"sldh",str);
	}
}

string check_schedule()
{
	mixed info;
	int tt,lvl;
	string str;
	if( base_name(environment())!="/d/kaifeng/yuwang5" )
        	return 0;	
	title = check_title();
	switch(Status)
	{
		case INVITE :
			str = "现在正在进行"+title+"第"+chinese_number(round)+"轮比赛，目前等待报名中。";break;
		case DELAY :
			str = "现在正在进行"+title+"第"+chinese_number(round)+"轮比赛，目前等待开始中。";break;
		case FIGHT :
			str = "现在正在进行"+title+"第"+chinese_number(round)+"轮比赛，目前比赛中。";break;
		case NONE :
		case DONE :
			if( round>=MAXROUND || !title )
			{
				if( Now_level<=0 || Now_level>=150 )
					lvl = 40;
				else	lvl = Now_level+10;
				round = 1;
				str = "现在无比赛，即将开始的是 "+chinese_number(lvl)+"以下级别比赛"+"第"+chinese_number(round)+"轮。";break;
			}
			else	
			{
				lvl = Now_level;
				str = "现在无比赛，即将开始的是 "+title+"第"+chinese_number(round+1)+"轮。";break;
			}	
	}
	info = filter_array(call_out_info(), (: $1[1]=="reset_init" :));
	if(sizeof(info)>=1 )
	{
		tt = info[0][2];
		str+= "下一场比赛将于"+CHINESE_D->chtime(tt)+"后举行。";
	}
	str+= "\n你可以使用 list 命令来查看各等级的奖励。\n";
	return str;	
}

int save()
{
        if( !environment() 
         || base_name(environment())!="/d/kaifeng/yuwang5" )
                return 0;	
	if( can_save!=1 )
                return 0;
        return ::save();
} 

void self_destroy(){ destruct(this_object()); }

int restore()
{
        if(clonep()) 
        {
                if(sizeof(filter_array(children(base_name(this_object())),(:clonep:)))>1) 
                {
                        can_save=0;
                        this_object()->move("/obj/empty");
                        call_out("self_destroy",1);
                        return 0;
                }
        }
        return ::restore();
}

string query_save_file()  { return "/data/npc/ymdh"; }

void create()
{
        restore();
        set_name("禹王爷", ({ "yuwang ye", "yuwang", "yu", "wang", "ye" }));
        set("title", "天御玉执");
        set("gender", "男性");
        set("age", 100);
        set_level(120);
        set_skill("force", 1200);
        set_skill("spells", 1200);
        set_skill("unarmed", 1200);
        set_skill("dodge", 1200);
        set_skill("parry", 1200);
        set("inquiry", ([
                "here":      "此乃禹王林，妖魔大会在此定期(schedule)举行也。\n",
                "?":         (: check_schedule :),
                "schedule" : (: check_schedule :),
                "妖魔大会":  "妖魔大会乃一迷宫大阵设在禹王林中，雾瘴蔽天妖魔野兽横行，玩家务必尽其全部本
领杀尽所有对手，伤亡不损元神，赢者自有重赏也。玩家使init申请大会开始，再使join参加大会。\n",
                "ymdh":      "妖魔大会乃一迷宫大阵设在禹王林中，雾瘴蔽天妖魔野兽横行，玩家务必尽其全部本
领杀尽所有对手，伤亡不损元神，赢者自有重赏也。玩家使init申请大会开始，再使join参加大会。\n",
        ]));
        set("env/test","HIM");
        setup();
        carry_object(0,"cloth",1)->wear();
        carry_object(0,"kui",1)->wear();
        carry_object(0,"shoes",1)->wear();
        remove_call_out("reset_init");
        call_out("reset_init",10+random(10));
}

void die ()
{
        object me = this_object();
        message_vision ("\n天上传来雷鸣般的声音：$N乃天御玉执也！\n",me);
        message_vision ("\n$N从地上甩袖爬将起来。\n",me);
	powerup(0,1);
}

void unconcious()
{
        die();
}

void init ()
{
        add_action ("do_init","init");
        add_action ("do_join","join");
        add_action ("do_list","list");
        add_action ("do_level","level");
        add_action ("do_start","start");
}

int do_level(string arg)
{
	int v;
        object me = this_player();
        if( base_name(environment())!="/d/kaifeng/yuwang5" )
                return 0;	
        if( SECURITY_D->get_status(me)!="(admin)" 
         && SECURITY_D->get_status(me)!="(arch)" )
                return 0;
	if( Status!=NONE && Status!=DONE )
		return err_msg("目前正在比赛中。"+Status+"\n");                
        if( !arg || sscanf(arg,"%d",v)!=1 )
        	return err_msg("命令格式 level <需要的等级, 40-150之间。\n");
        if( v<40 || v>150 )
        	return err_msg("命令格式 level <需要的等级, 40-150之间。\n");	
        Now_level = v;
        round = 1;
        set_status(NONE);
        Player = ([]);
        remove_call_out("reset_init");
        call_out("reset_init",LEVEL_TIME);
        write("ok,你将当前的大会等级调整为"+v+"。\n");                
	CHANNEL_D->do_channel(this_object(),"sldh",me->query("id")+"将妖魔大会等级调整为"+v+"以下级别。");        
        return 1;
}

varargs int check_players(int raw)
{
        object room, who;
        string *nameids;
        int i, j;
  
        room = environment();
        if( !room || base_name(room)!="/d/kaifeng/yuwang5" )
                return 0;
        nameids = keys(Player);
        if( !nameids || sizeof(nameids)<1 )
                return 0;
        i = sizeof(nameids);
        j = i;
        while(j--) 
        {
                who = Player[nameids[j]];
                if( !who ) 
                {
                        i--;
                        announce(nameids[j]+"临阵脱逃，退出大会。\n");
                        remove_player(nameids[j]);
                } 
                else if(((int)who->query("potential")-(int)who->query("learned_points"))<20) 
                {
                        i--;
                        announce(nameids[j]+"潜能不足，退出大会。\n");
                        remove_player(nameids[j]);
                }
                else if( raw && !environment(who)->is_ymdh() )
                {
                        announce(nameids[j]+"临阵脱逃，退出大会。\n");
                        remove_player(nameids[j]);
                        i--;
                } 
        }
        return i;
}

void start_ymdh(int max_player)
{
	object *pp;
	int j,i,now_player = check_players();
	remove_call_out("start_ymdh");
        if( base_name(environment())!="/d/kaifeng/yuwang5" )
                return;
	if( now_player<max_player )
	{
		set_status(INVITE);
		announce (title+"第"+chinese_number(round)+"场 人数不够，暂缓进行！\n");
		announce (title+"第"+chinese_number(round+1)+"场比赛即将开始，请各位踊跃报名！\n");
		announce (check_schedule()+"\n");
		return;
	}
	set_status(FIGHT);
	pp = values(Player);
        i = sizeof(pp);
        j = 0;
        while(i--)
        {
        	if( !pp[i] || !environment(pp[i])
        	 || environment(pp[i])->is_ymdh() )
        	 	continue;
		pp[i]->delete_temp("maze"); 
		pp[i]->set_temp("maze/公共地图","ymdh");
		if( MAZE_D->enter_maze(pp[i], "ymdh") ) 
		{
			pp->set_temp("maze/ymdh",time());
			pp->set_temp("maze/ymdh_ye",this_object());
			j++;
		}
        }
        announce (title+"第"+chinese_number(round)+"场现在开始，本场共有"+chinese_number(j)+"位参加者！\n");
        remove_call_out("reset_init");
        call_out("reset_init",ROUND_TIME);
}

int do_join()
{
	object me = this_player();
	if( me->query_level()<30 || me->query_level()>=150 )
		return err_msg("禹王爷对你摇摇头：你没有参加的资格。\n");
        if( base_name(environment())!="/d/kaifeng/yuwang5" )
                return 0;
	title = check_title();
	if( !title )
		return err_msg("禹王爷对你摇摇头："+check_schedule()+"\n");
	if( check_palyer_level(me)!=Now_level )
		return err_msg("禹王爷对你摇摇头：即将举行的是"+title+"比赛，你只能参加"+chinese_number(check_palyer_level(me))+"以下级别的。\n");
	if( !Player )
		Player = ([ me->query("id") : me,]);
	else
	{
		if( member_array(me->query("id"),keys(Player))!=-1 )
			return err_msg("禹王爷对你摇摇头：你已经报名了。\n");			
		Player[me->query("id")] = me;
	}
	message_vision("$N朝$n点了点头。\n$n报名参加了"+title+"比赛。\n",this_object(),me);
	return 1;	
}

int do_init()
{
	object me = this_player();
	mixed info;
	int j,i,remain;
	if( me->query_level()<30 || me->query_level()>=150 )
		return err_msg("禹王爷对你摇摇头：你没有参加的资格。\n");
        if( base_name(environment())!="/d/kaifeng/yuwang5" )
                return 0;	
	switch(Status)
	{
		case FIGHT  : return err_msg("禹王爷对你摇摇头：妖魔大会"+title+"比赛已经开始。\n");
		case DELAY  : return err_msg("禹王爷对你摇摇头："+title+"正在准备中，即将开始！\n");
		case NONE   :
			title = check_title();
			if( !title )
			{
				Now_level = 40;
				round = 1;
				title = check_title();
			}
			if( check_palyer_level(me)!=Now_level )
				return err_msg("禹王爷对你摇摇头：即将举行的是"+title+"比赛，你只能参加"+chinese_number(check_palyer_level(me))+"以下级别的。\n");
                        announce(me->query("name")+"前来邀请各位玩家参加"+title+"第"+chinese_number(round)+"场比赛！\n");
                        if(round==1)
                        	announce("妖魔大会乃一迷宫大阵设在禹王林中，雾瘴蔽天妖魔野兽横行，玩家务必尽其全部本领杀尽所有对手，伤亡不损元神，赢者自有重赏也。\n");
			remove_call_out("reset_init");
                        call_out("reset_init",ROUND_TIME);
			set_status(INVITE);
			Player = ([]);
                        me->command("join");
			return 1;			
		case INVITE :
			i = sizeof(users()) / 30;
                        if(i < 3) i = 3;
                        if( wizardp(me) && me->query("env/test") )
                        	i = 1;
                        j = check_players();
			if(j < i) 
                        	return err_msg("禹王爷对你摇摇头："+title+"尚需"+chinese_number(i-j)+"名玩家参加方可举行也。\n");
			announce (title+"第"+chinese_number(round)+"场将于一分种后开始！玩家准备入场就位！\n");
                        set_status(DELAY);
                        call_out("start_ymdh", 60, i);
                        return 1;
		case DONE   :
			info = filter_array(call_out_info(), (: $1[1]=="reset_init" :));
			if(sizeof(info)<1)
				return err_msg("$禹王爷对你摇摇头：妖魔大会已经结束。\n");
			remain = info[0][2];
			return err_msg("禹王爷对你说道："+title+"将于"+CHINESE_D->chtime(remain)+"后举行！到时您再来吧。\n");
	}
}

void reward_obj(object who)
{
	int i,lvl;
	object obj;
	string *rewards,str,file;
	if( !who || !living(who) )
		return;
	if( !environment() || base_name(environment())!="/d/kaifeng/yuwang5" )
		return;
	lvl = check_palyer_level(who);
	if( undefinedp(Rewards[lvl]) )
		return;
	if( who->query_temp("ymdh/yaomokilled")<=0 )
	{
		tell_object(who,HIW"【系统】妖魔大会：你在大会中未有建树，故未获得赢家奖品。"NOR"\n");
		return;
	}		
	rewards = Rewards[lvl];
	i = 2+random(3);
	str = "";
	while(i--)
	{
		file = rewards[random(sizeof(rewards))];
		obj = new("/d/maze/ymdh/obj/"+file);
		if( obj->move(who) )
		{
			tell_object(who,HIW"【系统】妖魔大会：你得到了"+obj->name()+HIW"。"NOR"\n");
			str+= obj->name()+" ";
		}
		else	destruct(obj);
	}
	announce("兹奖励"+who->name()+str+"。"NOR"\n");				
}

void remove_all_player()
{
	int i;
	object maze,*obj;
	if( !Player )
		return;
	if( !environment() || base_name(environment())!="/d/kaifeng/yuwang5" )
		return;	
	obj = values(Player);
	if( !obj || !arrayp(obj) || sizeof(obj)<1 )
		return;
	for(i=0;i<sizeof(obj);i++)
	{
		if( !environment(obj[i]) 
		 || !environment(obj[i])->is_ymdh() )
		 	continue;
		 tell_object(obj[i],"\n\n浓雾散去，你慢慢退出了比赛。\n");
		 obj[i]->delete_temp("maze");
		 obj[i]->delete_temp("ymdh");
		 obj[i]->move(sprintf("/d/kaifeng/yuwang%d",1+random(5)));
	}
	maze = find_object("/data/maze/ymdh/ymdh/maze.c");
	if( !maze )
		maze = load_object("/data/maze/ymdh/ymdh/maze.c");
	if( !maze )
		return;
	maze->refresh_maze();
	CHANNEL_D->do_channel(this_object(),"sys","妖魔大会副本地图已清除。");	
}

void new_round()
{
	object *obj,who;
	remove_call_out("reset_init");
	if( !environment() || base_name(environment())!="/d/kaifeng/yuwang5" )
		return;
	if( check_players(1)!=1 )
	{
		if( check_players(1)>1 )
			announce(title+"第"+chinese_number(round)+"场时间用尽，不分胜负！即将进行下一场！请继续报名参加。\n");
		else	announce(title+"第"+chinese_number(round)+"场时间已尽，即将进行下一场！请继续报名参加。\n");
	}	
	else
	{
		obj = values(Player);
		who = obj[0];
		if( who )
		{
			if( !Wins )
				Wins = ({who->query("id")});
			else	Wins+= ({who->query("id")});
			announce (title+"第"+chinese_number(round)+"场结束！嬴家："+who->query("name")+"！即将进行下一场！请继续报名参加。\n");
			reward_obj(who);
		}
		else	announce(title+"第"+chinese_number(round)+"场时间已尽，即将进行下一场！请继续报名参加。\n");
	}
	remove_all_player();
	Player = ([]);
	set_status(NONE);
	call_out("reset_init",ROUND_TIME);	
}

void new_level()
{
	remove_call_out("reset_init");
	if( !environment() || base_name(environment())!="/d/kaifeng/yuwang5" )
		return;
	title = check_title();
	if( title )
		announce (title+"比赛结束！\n");
	if( Now_level==0 || Now_level==150 )
		Now_level = 40;
	else	Now_level+= 10;
	round = 1;
	title = check_title();
	announce(title+"第"+chinese_number(round)+"场即将开始！请报名参加。\n");
	can_save = 1;
	save();
	can_save = 0;	
	call_out("reset_init",LEVEL_TIME);
}

void reset_init()
{
        object me = this_object();
        object room = environment();

        remove_call_out("reset_init");
        if( !room || base_name(room)!="/d/kaifeng/yuwang5" )
                return;
	switch(Status)
	{
		case FIGHT :
		case NONE :	
		case DONE :
		case INVITE :
			if( Status==INVITE )
				announce(title+"第"+chinese_number(round)+"场本场轮空！\n");
			round = round+1;
			title = check_title();
			if( round>MAXROUND || !title )
				new_level();
			else	new_round();
			break;
		case DELAY :
			break;
	}
	can_save = 1;
	save();
	can_save = 0;
}

int do_list()
{
	string str;
	str = @LONG
妖魔大会奖品一览：
	40以下级别：
		一两黄金 五两黄金 十两黄金  筑基丹  
		送信任务低阶道行丹、经验丹、潜能丹
		天监灭妖低阶道行丹、经验丹、潜能丹
		门派任务低阶道行丹、经验丹、潜能丹
	50以下级别：
		五两黄金  十两黄金  固元丹
		送信任务低阶道行丹、经验丹、潜能丹
		天监灭妖低阶道行丹、经验丹、潜能丹
		门派任务低阶道行丹、经验丹、潜能丹
		天监灭妖中阶道行丹、经验丹、潜能丹
	60以下级别：
		五两黄金  十两黄金  破元丹
		天监灭妖中阶道行丹、经验丹、潜能丹
		门派任务中阶道行丹、经验丹、潜能丹
	70以下级别：
		五两黄金  十两黄金  破心丹
		天监灭妖中阶道行丹、经验丹、潜能丹
		门派任务中阶道行丹、经验丹、潜能丹
		天监灭妖上阶道行丹、经验丹、潜能丹
		门派任务上阶道行丹、经验丹、潜能丹
	80以下级别：
		五十两黄金 十两黄金 结金丹
		天宫灭妖低阶道行丹、经验丹、潜能丹
		门派任务上阶道行丹、经验丹、潜能丹
	90以下级别：
		五十两黄金 一百两黄金 结婴丹
		天宫灭妖低阶道行丹、经验丹、潜能丹
		门派任务上阶道行丹、经验丹、潜能丹
		天宫灭妖中阶道行丹、经验丹、潜能丹
	100以下级别：
		五十两黄金  一百两黄金
		天宫灭妖中阶道行丹、经验丹、潜能丹
		门派任务上阶道行丹、经验丹、潜能丹
	110以下级别：
		五十两黄金  一百两黄金  
		天宫灭妖中阶道行丹、经验丹、潜能丹
		天宫灭妖上阶道行丹、经验丹、潜能丹
		门派任务上阶道行丹、经验丹、潜能丹
	120以下级别：
		五十两黄金  一百两黄金  
		天宫灭妖上阶道行丹、经验丹、潜能丹
		门派任务上阶道行丹、经验丹、潜能丹
	130以下级别：
		五十两黄金  一百两黄金  
		天宫灭妖上阶道行丹、经验丹、潜能丹
		门派任务上阶道行丹、经验丹、潜能丹
	140以下级别：
		五十两黄金  一百两黄金  
		天宫灭妖上阶道行丹、经验丹、潜能丹
		门派任务上阶道行丹、经验丹、潜能丹
	150以下级别：
		五十两黄金  一百两黄金
		天宫灭妖上阶道行丹、经验丹、潜能丹
		门派任务上阶道行丹、经验丹、潜能丹
注：突破仙丹
	40级突破-筑基丹   50级突破-固元丹   60级突破-破元丹
	70级突破-破心丹   80级突破-结金丹   90级突破-结婴丹
    奖励加成仙丹
    	低阶-3小时内相应奖励加成10%(不包括全局奖励加成)
    	中阶-3小时内相应奖励加成25%(不包括全局奖励加成)
    	上阶-3小时内相应奖励加成50%(不包括全局奖励加成)
	
LONG;	
	this_player()->start_more(str);
	return 1;
}	
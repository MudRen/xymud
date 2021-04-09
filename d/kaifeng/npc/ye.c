#include <ansi.h>
inherit NPC;
inherit F_SAVE;
#include "/cmds/std/valid_move.h"

#define NONE 0
#define INVITE 1
#define FIGHT 3
#define DONE 7
#define DELAY 10

#define BONUS 1000
#define INTERVAL  9000   //3600
#define SUB_INTERVAL 1200
#define FIGHT_DURATION 1500
#define MAXROUND 5

//#define NEXT_GAME (INTERVAL-FIGHT_DURATION*sizeof(levels))

int *levels=({600,1000,400,800,200,});
int NEXT_GAME = (INTERVAL-FIGHT_DURATION*sizeof(levels));
int level=0;
int NowI = 0;
string title;
int can_save=1;
int wizlock = 0;

mapping Player = ([]);

int round=MAXROUND;
int bonus=BONUS;
int STATUS = 0;

string *winner=({});
string *winip = ({});

string *reward=({
	"/quest/xuanwu/obj/1",
    "/quest/xuanwu/obj/2",
    "/quest/xuanwu/obj/3",
	"/d/obj/misc/armor_bd5",
	"/d/obj/misc/weapon_bd",
	"/d/obj/misc/weapon_sj",
	"/d/obj/misc/armor_sj",	
});

string query_save_file()  { return "/data/npc/ymdh"; }

void announce (string str);
void set_status (int i);
void ym_title(int year);
string check_title(int year);
int random_action();
void start_ymdh(int i);
void deduct_pot();
int query_status();
void reset_init();
int get_level() { return level; }
void set_level(int v) { level = v;}

int wizlock(){ return wizlock==0?0:1; }

int save()
{
        if( can_save!=1 )
                return 0;
        return ::save();
}       

void self_destroy()
{
        if(this_object())
                destruct(this_object());
}

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

void next_level() 
{
        level++;
        if(level>=sizeof(levels)) 
                level=0;
        ym_title(levels[level]);
        round=MAXROUND;
        set_status(NONE);
        remove_call_out("reset_init");
        call_out("reset_init", SUB_INTERVAL);
        tell_room(environment(this_object()),title+"\n");
}

string convert_time(int t)
{
        int hour=t/60;
        int min=(t-hour*60);
        string str="";
        
        if(t<1) {hour=0;min=1;}
        if(hour) str=chinese_number(hour)+"小时";
        if(min) str+=chinese_number(min)+"分钟";
        return str;
}

string check_schedule()
{
        int i=sizeof(levels);
        int k=i, j=level, remain=0;
        mixed info;
        string str;

        info = filter_array(call_out_info(), (: $1[1]=="reset_init" :));
        if(sizeof(info)>=1) // should be only 1.
                remain=info[0][2];
        
        str="\n\n";
        if(query_status()!=DONE) 
        {
                str+=sprintf("%-24s：　正在举行\n",title);
                j=j+1; k=k-1;
                remain=INTERVAL;
        } 
        while(k--) 
        {
                if(j>=i) j=0;
                str+=sprintf("%-24s：　约于%s后举行\n",check_title(levels[j]),convert_time(remain/60));
                j++;
                remain+=INTERVAL;
        }
        str+="\n";
        return str;
}

void set_bonus(int i)
{
//    bonus=BONUS; // can set variable bonus depending # of players.
        if(i<10) bonus=0;
        else 
        {
                bonus=BONUS/MAXROUND+(i-10)*5;
                if(bonus>2*BONUS/MAXROUND) bonus=2*BONUS/MAXROUND;
        }
}

void create()
{
        restore();
        set_name("禹王爷", ({ "yuwang ye", "yuwang", "yu", "wang", "ye" }));
        set("title", "天御玉执");
        set("gender", "男性");
        set("age", 100);
        set("per", 30);
        set("combat_exp", 300000);
        set_skill("force", 310);
        set_skill("spells", 310);
        set_skill("unarmed", 310);
        set_skill("dodge", 310);
        set_skill("parry", 310);
        set("max_kee", 3000);
        set("max_sen", 3000);
        set("max_force", 1000);
        set("max_mana", 1000);
        set("force_factor", 310);
        powerup();
        set("inquiry", ([
                "here":      "此乃禹王林，妖魔大会在此定期(schedule)举行也。\n",
                "?":         (: check_schedule :),
                "妖魔大会":  "妖魔大会乃一迷宫大阵设在禹王林中，雾瘴蔽天妖魔野兽横行，玩家务必尽其全部本
领杀尽所有对手，伤亡不损元神，赢者自有重赏也。玩家使init申请大会开始，再使join参加大会，巫师可使chaxun来获得巫师命令。\n",
                "ymdh":      "妖魔大会乃一迷宫大阵设在禹王林中，雾瘴蔽天妖魔野兽横行，
玩家务必尽其全部本领杀尽所有对手，伤亡不损元神，赢者自有重赏也。
玩家用schedule查询赛程，watch id观看别人比赛，使init申请大会开始，
再使join参加大会，巫师可使chaxun来获得巫师命令。\n",
                "schedule":  (: check_schedule :),
        ]));
        setup();
        carry_object("/d/obj/cloth/jinpao")->wear();
        if(clonep() )
        {
                set_status(NONE);
                Player = ([]);
                level=get_level();
                title = check_title(levels[get_level()]);
//                round=MAXROUND;
//                announce(title+"第"+chinese_number(MAXROUND-round+1)+"场比赛现在开始！\n");
                remove_call_out("reset_init");
                call_out("reset_init",SUB_INTERVAL);
        }
}

string check_title(int year)
{
        string str;
        str = sprintf(" %s级妖魔大会 ",chinese_number(year));
        return str;
}

void ym_title(int year)
{
        title=check_title(year);
}

void announce (string str)
{
          if( environment() )
                CHANNEL_D->do_channel(this_object(),"sldh",str);
}

int query_status() { return STATUS; }

void set_status (int i) { STATUS = i; }

void init ()
{
        add_action ("do_init","init");
        add_action ("do_join","join");
        add_action ("do_list","list");
        add_action ("do_chaxun","chaxun");
        add_action ("do_wizlock","lock");
        add_action ("do_level","level");
        add_action ("do_start","start");
}

int err_msg(string arg)
{
        write(arg);
        return 1;
}

int do_list()
{
        int i;
        string *name,str;
        object me = this_player();
        name = keys(Player);
        if( sizeof(name)<1 )
                return err_msg("妖魔大会尚未开始。\n");
        str = title+"第"+chinese_number(MAXROUND-round+1)+"场比赛目前玩家有：\n";
        for(i=0;i<sizeof(name);i++)
                str+= "\t\t"+name[i]+"\n";
        me->start_more(str);
        return 1;
}                               

int do_start()
{
        object me = this_player();
        if( SECURITY_D->get_status(me)!="(admin)" 
         && SECURITY_D->get_status(me)!="(arch)" )
                return 0;
        if( STATUS!=DELAY )
                return err_msg("妖魔大会尚未开始。\n");
        if( me->is_busy() )
                return err_msg("你现在正忙。\n");               
        remove_call_out("start_ymdh");
        start_ymdh(NowI);
        me->start_busy(3);
        return 1;
}

int do_chaxun()
{
        string str;
        object me = this_player();
        if( SECURITY_D->get_status(me)!="(admin)" 
         && SECURITY_D->get_status(me)!="(arch)" )
                return 0;
        str = "\n";
        str+= HIR"\n
        命令                    作用                    使用者\n"NOR;
        str+= HIG"
        lock <off/on>"HIY"      测试模式开关，测试模    "HIW"<admin>"HIY"
                                式下奖励不兑现。        "HIG"
        level <等级>    "HIY"   使当前的大会为设定的    "HIW"<admin|arch>"HIY"
                                等级"HIY"
        start           "HIY"   立即开始当前的大会      "HIW"<admin|arch>\n"NOR;
        write(str);
        return 1;
}

int do_wizlock(string arg)
{
        string str;
        object me = this_player();
        if( SECURITY_D->get_status(me)!="(admin)" )
                return err_msg("你的权限不够。\n");
        if( !arg )
                arg = "on";
        if( arg!="off" && arg!="on" )
                return err_msg("命令格式 wizlock <off/on>\n");
        if( arg=="off" )
        {
                if( wizlock==0 )
                        return err_msg("没有必要，现在就是正常模式。\n");
                wizlock = 0;
                str = sprintf("%20-s %s 关闭了妖魔大会的测试模式。\n",ctime(time()),me->query("id"));
                write_file("/c/log/ymdh/wizcmds",str);
                announce(me->name(1)+"关闭了妖魔大会的测试模式。");
                write("设置完毕，当前模式为正常模式。\n");
                return 1;
        }
        else
        {
                if( wizlock!=0 )
                        return err_msg("没有必要，现在就是测试模式。\n");
                wizlock++;
                str = sprintf("%20-s %s 开启了妖魔大会的测试模式。\n",ctime(time()),me->query("id"));
                write_file("/c/log/ymdh/wizcmds",str);
                announce(me->name(1)+"开启了妖魔大会的测试模式。");
                write("设置完毕，当前模式为测试模式。\n");
                return 1;
        }
}

int do_level(string arg)
{
        int i,k,lvl;
        string str;
        object me = this_player();
        if( SECURITY_D->get_status(me)!="(admin)" 
         && SECURITY_D->get_status(me)!="(arch)" )
                return 0;
        if( !arg || sscanf(arg,"%d",lvl)!=1 )
                return err_msg("命令格式 level <等级>\n");
        if( STATUS!=NONE && STATUS!=DONE )
                return err_msg("目前的状态不允许随意更改大会等级。\n");         
        if( level==lvl )
                return err_msg("没有必要，当前的等级就是"+lvl+"。\n");          
        if( member_array(lvl,levels)==-1 )
        {
                str = "你所要求的等级不存在于任务阵列，当前可要求的等级为：";
                for(i=0;i<sizeof(levels);i++)
                        str+= ""+levels[i]+" ";
                str+= "\n";
                return err_msg(str);
        }
        for(i=0;i<sizeof(levels);i++)
        {
                if( levels[i]==lvl )
                {
                        k = i;
                        break;
                }
        }       
        set_level(k);
        set_status(NONE);
        Player = ([]);
        level=get_level();
        title = check_title(levels[get_level()]);
        round=MAXROUND;
        save();
        announce(title+"第"+chinese_number(MAXROUND-round+1)+"场比赛现在开始！\n");
        remove_call_out("reset_init");
        call_out("reset_init",SUB_INTERVAL);
        write("ok,你将当前的大会等级调整为"+lvl+"。\n");                
        str = sprintf("%20-s %s 将妖魔大会的等级调整为 %d 。\n",ctime(time()),me->query("id"),lvl);     
        return 1;
}       
                        
void escaped(string nameid)
{
        string str;
        str = "妖魔大会："+nameid+"临阵逃脱了。\n";
        announce(str);
        map_delete(Player,nameid);
}

void remove_player(string nameid)
{
        map_delete(Player,nameid);
}

void deduct_pot()
{
        object me = this_object();
        object room;
        string *nameids;
        int j;
  
        room = environment();
        if( !room || base_name(room)!="/d/kaifeng/yuwang5" )
                return 0;
        nameids = keys(Player);
        if( !nameids || sizeof(nameids)<1 )
                return 0;
        map_delete(Player,0);           
        j = sizeof(nameids);
        while (j--) 
        {
                if( !Player[nameids[j]] )
                {
                        escaped(nameids[j]);
                        continue;
                }
                Player[nameids[j]]->add("combat_exp",-3000);
                tell_object(Player[nameids[j]],"你的武学修为减少了三千点！\n");
                Player[nameids[j]]->add("daoxing",-3000);
                tell_object(Player[nameids[j]],"你的道行修为减少了三千点！\n");
        }
}

int check_players ()
{
        object me = this_object();
        object room, who;
        string *nameids;
        int i, j;
  
        room = environment(me);
        if( !room || base_name(room)!="/d/kaifeng/yuwang5" )
                return 0;

        nameids = keys(Player);
        if( !nameids || sizeof(nameids)<1 )
                return 0;
        i = sizeof(nameids);
        j = i;
        while (j--) 
        {
                who=Player[nameids[j]];
                if(! Player[nameids[j]]) 
                {
                        i--;
                        announce(nameids[j]+"临阵脱逃，退出大会。\n");
                        map_delete(Player,nameids[j]);
                } 
                else if(((int)who->query("potential")-(int)who->query("learned_points"))<20) 
                {
                        i--;
                        announce(nameids[j]+"潜能不足，退出大会。\n");
                        map_delete(Player,nameids[j]);
                }
        }
        return i;
}

void reset_init()
{
        object me = this_object();
        object room = environment();
        mapping players;

        remove_call_out("reset_init");
        if( !room || base_name(room)!="/d/kaifeng/yuwang5" )
                return;

        if( STATUS!= FIGHT ) 
        {
                round--; // if no one plays reduce round.
                if(round<=0) 
                {
                        set_status(DONE);
                        call_out("reset_init", NEXT_GAME);
                        winner=({});
                        winip=({});
                        level++;
                        round=MAXROUND+1;
                        if(level>=sizeof(levels)) level=0;
                        if( sizeof(Player)>1 )
                                announce(title+"时间用尽，");
                        ym_title(levels[level]);
                        if( sizeof(Player)>1 ) 
                        {
                                Player = ([]);
                                save();
                                announce(title+"将于"+chinese_number((NEXT_GAME+1800)/3600)+"小时后举行！\n");
                        }
                } 
                else 
                {
                        winner=({});
                        winip=({});
                        set_status(NONE);
                        if(round>=MAXROUND) 
                        {
                                announce(title+"现在开始！\n");
                                Player = ([]);
                                save();
                                call_out("reset_init",SUB_INTERVAL);
                                return;
                        }
                        if( sizeof(Player)>1 )                  
                        {
                                announce(title+"第"+chinese_number(MAXROUND-round)+"场时间已尽，现在进行下一场！请继续报名参加。\n");
                                call_out("reset_init", SUB_INTERVAL);
                        } 
                        else 
                        {
                                Player = ([]);
                                round=1; // no one join, then finish this meeting.
                                save();
                                reset_init();
                        }
                }
        } 
        else 
        {
                Player = ([]);
                announce(title+"第"+chinese_number(MAXROUND-round+1)+"场时间用尽，不分胜负！\n");
                room->checks();
                save();
        }
}

int max_skill(object who)
{
        int i,Max = 0;
        mapping skill;
        string *skills;
        if( !who )
                return 0;
        skill = who->query_skills();
        if( !skill || !mapp(skill) )
                return 0;
        skills = keys(skill);
        if( sizeof(skills)<1 )
                return 0;
        for(i=0;i<sizeof(skills);i++)
        {
        	if( skills[i]=="literate" )
        		continue;
			if( skill[skills[i]]>Max )
            	Max = skill[skills[i]];
		}            	
//200,400,600,800,1000,
        if( Max<=200 )
                return 200;
        else if( Max<=400 )
                return 400;
        else if( Max<=600 )
                return 600;                                     
        else if( Max<=800 )
                return 800;     
        else    return 1000;                            
}                       

void check_rzr(string file)
{
        object *obj,npc;
        int i,f = 0;

        if( !file )
                return;

        obj = children("/quest/rzr/"+file+levels[get_level()]);
        if( obj && arrayp(obj) )
        {
                for(i=0;i<sizeof(obj);i++)
                {
                        if( !obj[i] )
                                continue;
                        if( Player[obj[i]->query("name")+"("+obj[i]->query("id")+")"] == obj[i]
                         && environment(obj[i])
                         && present(obj[i],environment()) )
                                return;                                         
                        if( environment(obj[i]) )
                        {
                                message_vision(HIW"\n$N说道：「不打了，不打了，我投降....。」\n"NOR,obj[i]);
                                obj[i]->command("say 我去参加妖魔大会去也！\n");
                                message_vision("$N急急忙忙的离开了。\n",obj[i]);
                        }
                        destruct(obj[i]);
                }
        }
        npc = new("/quest/rzr/"+file+levels[get_level()]);
        if( npc && npc->move(environment()) )
        {
                message_vision("\n$N走了过来。\n",npc);
                npc->add("potential",40);
                npc->command("join");
                return;
        }
        else
        {
                destruct(npc);
                return;
        }
}                                       

int do_init (string arg)
{
        object *obj;
        object me = this_object();
        object who = this_player();
        object room = environment(me);
        int i, j, exp, low, high,lvl,k;
        string *files,file;

        if( !room || base_name(room)!="/d/kaifeng/yuwang5" )
                return 0;
        exp = max_skill(who);
        if( exp!=levels[get_level()] )
        {
                message_vision ("$N对$n摇摇头：以汝之技能，只能前往参加"+exp+"等级的比赛，现在举行的是"+levels[get_level()]+"级的比赛。\n",me,who);
                return 1;
        }
        if( !valid_move(who) )
        {
                tell_object(who,"你现在的状态不能参加妖魔大会。\n");
                return 1;
        }
        switch(STATUS)
        {
                case DONE :  {
                                mixed info; // mon
                                info = filter_array(call_out_info(), (: $1[1]=="reset_init" :));
                                if(sizeof(info)>=1) 
                                { // should be only 1.
                                        int remain=info[0][2]/60+1;
                                        int hour=remain/60;
                                        int min=(remain-hour*60);
                                        string str="";
                                        if(hour) str=chinese_number(hour)+"小时";
                                        if(min) str+=chinese_number(min)+"分钟";
                                        message_vision("$N对$n说道："+title+"将于"+str+"后举行！到时您再来吧。\n",me,who);
                                } 
                                else    message_vision ("$N对$n摇摇头：妖魔大会已经结束。\n",me,who);
                                return 1;
                           }
                case FIGHT :    message_vision ("$N对$n摇摇头：妖魔大会已经开始。\n",me,who);
                                return 1;
                case INVITE: 
                                i = sizeof(users()) / 30;
                                if(i < 3) i = 3;
                                if( wizardp(who) && wizhood(who)=="(admin)" )   i = 1;                       
                                j = check_players();
                                if(j < i) 
                                {
                                        message_vision ("$N对$n摇摇头："+title+"尚需"+chinese_number(i-j)+"名玩家参加方可举行也。\n",me,who);
                                        return 1;
                                }
                                announce (title+"第"+chinese_number(MAXROUND-round+1)+"场将于一分种后开始！玩家准备入场就位！\n");
                                set_status(DELAY);
                                NowI = i;
                                call_out("start_ymdh", 60, i);
                                return 1;
                case DELAY :    
                                message_vision ("$N对$n摇摇头："+title+"正在准备中，即将开始！\n",me,who);
                                return 1;
                default    : 
                                title = check_title(levels[get_level()]);
                                announce(who->query("name")+"前来邀请各位玩家参加"+title+"第"+chinese_number(MAXROUND-round+1)+"场比赛！\n");
                                if(round==MAXROUND)
                                        announce("妖魔大会乃一迷宫大阵设在禹王林中，雾瘴蔽天妖魔野兽横行，玩家务必尽其全部本领杀尽所有对手，伤亡不损元神，赢者自有重赏也。\n");
                                remove_call_out("reset_init");
                                call_out("reset_init",SUB_INTERVAL);
                                set_status(INVITE);
                                who->command("join");
                                return 1;
        }
}

void start_ymdh(int i)
{
        int j = check_players();
        object room = environment();

        if( STATUS!=DELAY) 
                return;
        if(j<i) 
        {
                set_status(INVITE);
                announce(title+"玩家人数不够了！\n");
                return;
        }
        deduct_pot();
        announce (title+"第"+chinese_number(MAXROUND-round+1)+"场比赛现在开始！玩家入场就位！\n");
        room->start(levels[level],0);
        set_status(FIGHT);
        remove_call_out("reset_init");
        call_out("reset_init",FIGHT_DURATION);
}

int do_join (string arg)
{
        object me = this_object();
        object who = this_player();
        object room = environment(me);
        string str, id=who->query("id"),ip = query_ip_number(who);
        int i, exp, low, high;

        if( !room || base_name(room)!="/d/kaifeng/yuwang5" )
                return 0;
        exp = max_skill(who);
        low = 120;
        high = levels[level];
        if(high<=120) low=120;
        if(high>=2000) high=2000;

        exp = max_skill(who);
        if( exp!=levels[get_level()] )
        {
                message_vision ("$N对$n摇摇头：以汝之技能，只能前往参加"+exp+"等级比赛。\n",me,who);
                return 1;
        }

        if(((int)who->query("potential")-(int)who->query("learned_points"))<20) 
        {
                message_vision ("$N对$n摇摇头：潜能不足也。\n",me,who);
                return 1;
        }

        if(exp>high) 
                exp = high;

        //mon 禁止垄断
        if((i=member_array(id, winner))>-1)  
        {
                if(i<(sizeof(winner)-1))
                        if(member_array(id, winner, i+1)>-1) 
                        {
                                message_vision("$N对$n摇摇头：您已经赢两次了，"+"给别人留点机会吧：）\n",me,who);
                                return 1;
                        }
        }
        if((i=member_array(ip, winip))>-1)  
        {
                if(i<(sizeof(winip)-1))
                        if(member_array(ip, winip, i+1)>-1) 
                        {
                                message_vision("$N对$n摇摇头：您已经赢两次了，"+"给别人留点机会吧：）\n",me,who);
                                return 1;
                        }
        }
        if(who->query_condition("no_pk_time")) 
        {
                message_vision ("$N对$n摇摇头：您刚杀过人，还是等会儿再来吧！\n",me,who);
                return 1;
        }
        if(query_status() == DONE) 
        {
                message_vision ("$N对$n摇摇头：妖魔大会已经结束。\n",me,who);
                return 1;
        }
        if(query_status() == FIGHT) 
        {
                message_vision ("$N对$n摇摇头：妖魔大会已经开始。\n",me,who);
                return 1;
        }
        if( query_status() == INVITE 
         || query_status() == DELAY) 
        {
                str = who->query("name")+"("+who->query("id")+")";
                if( Player[str]) 
                {
                        message_vision ("$N对$n摇摇头：妖魔大会您已在邀也。\n",me,who);
                        return 1;
                }
                Player[str] = who;
                announce (title+str+"前来应邀！\n");
                NEXT_GAME = (INTERVAL-FIGHT_DURATION*sizeof(levels));
                if( wizardp(who) )  tell_object(who,"nextgame="+NEXT_GAME+"\n");
                if( userp(who) )
                {
                        if( check_players()==1 )
                                check_rzr("shushan");
                        else if( check_players()==3 )
                                check_rzr("wdd");       
                        else if( check_players()==5 )
                                check_rzr("xs");        
                }
                return 1;
        }
        message_vision ("$N对$n摇摇头："+title+"尚未开始。\n",me,who);
        message_vision ("$N说道：请使init命令也。\n",me,who);
        return 1;
}

void report (string str)
{
        announce ("妖魔大会场内尚有玩家："+str+"。\n");
}

void finish (object who)
{
        string str;
        int ss,i = bonus;
        announce (title+"第"+chinese_number(MAXROUND-round+1)+"场结束！嬴家："+(who?who->query("name"):"(无)")+"！\n");
  
        reset_eval_cost();
        // mon
        round--;
        if(round<=0) 
        {
                set_status(DONE);
                remove_call_out("reset_init");
                call_out("reset_init",NEXT_GAME);
                winner=({});
                winip=({});
                level++;
                round=MAXROUND+1;
                if(level>=sizeof(levels)) level=0;
                ym_title(levels[level]);
        } 
        else 
        {
                remove_call_out("reset_init");
                set_status(NONE);
                call_out("reset_init",SUB_INTERVAL); // mon
        }

        if(who) 
        {
                object ob;
                int kill_bonus=1000;
                int multiplier=who->query_temp("ymdh/yaomokilled");
      
                who->delete_temp("ymdh/yaomokilled");
                if(multiplier<0) multiplier=0;
                if(multiplier>50) multiplier=50;
                kill_bonus*=multiplier;
                kill_bonus+= 5000+random(10000);
                str = who->query("name")+"共杀死"+chinese_number(multiplier)+"妖魔，故奖"+who->query("name")+chinese_number(kill_bonus)+"点潜能";
                
                ss = levels[level];
                if( wizardp(who) )  tell_object(who,"ss="+ss+"\n");
                
                ss/= 100; //2-4-6-8-10
                ss+= 10; //12 14 16 18 20            
                if( (random(ss)>10 ||wizardp(who)) && multiplier>0 
                 && (17+who->query("obstacle/rebirth"))>0 )
                {
                        if( wizlock<=0 )
                                who->add("obstacle/rebirth",-1);  
                        tell_object(who,"你得到了一根救命毫毛的奖励。\n");   
                        str+= "、救命毫毛";
                }
                if( random(2)==0 || wizardp(who) )
                {
                        ob=new(reward[random(sizeof(reward))]);
                        if( ob )
                        {
                                str+= "、"+ob->name();
//                                if( wizlock==0 && ob->move(who) )
                                if( ob->move(who) )
                                        tell_object(who,"你得到了一"+ob->query("unit")+ob->name()+"。\n");
                                else    destruct(ob);
                        }
                }
                if( wizlock!=0 )
                        str+= "，因为测试期间，所以以上奖励没有兑现。\n";                       
                else    str+= "。\n";
                str = COLOR_D->clean_color(str);
                str = NOR WHT+str+NOR;
                str = COLOR_D->replace_color(str,1);
                announce(str);
                who->add("potential",kill_bonus);
                who->save();
                if( who && !userp(who) && who->is_rzr() )  {
                          who->clear_condition();
                          who->remove_all_killer();
                          who->die();
                          return;
                }
                log_file("ymdh",who->query("id")+" got "+kill_bonus+" qianneng.\n");
                if( !wizardp(who) && !who->is_rzr() )
                        {
                            winner+=({who->query("id")});
                            winip+= ({query_ip_number(who)});
                        }
        }
        Player = ([]);
        save();
}

void die ()
{
        object me = this_object();

        message_vision ("\n天上传来雷鸣般的声音：$N乃天御玉执也！\n",me);
        message_vision ("\n$N从地上甩袖爬将起来。\n",me);
        set("kee", 3000);
        set("sen", 3000);
        me->clear_condition();
}

void unconcious()
{
        die();
}

void accept_fight (object ob)
{
        object me = this_object();
        message_vision ("$N连忙闪身：老夫有天御玉执在身，失陪！\n",me);
}

void kill_ob (object ob)
{
        object me = this_object();

        message_vision ("$N连忙闪身：老夫有天御玉执在身，失陪！\n",me);
        me->remove_all_killer();
        all_inventory(environment(me))->remove_killer(me);
}

mapping query_player()
{
        return Player;
}

int valid_data()
{
        Player = ([]);
        winner = ({});
        winip = ({});
        round=MAXROUND;
        bonus=BONUS;
        STATUS = 0;
        level = 0;
        if( environment() )
                environment()->checks();
        return save();
}

void reward_ob(object killer,string name)
{
        string str, msg;
        int reward;
        
        if( !killer ) 
                return;
        reward = 1000;
        reward = reward/4+random(reward/2);
		str = chinese_number(reward)+"点潜能";
		tell_object(killer,"\n你得到了"+str+"！\n");
        if( wizlock==0 ) killer->add("potential",reward);
        str = sprintf("%s打死了%s，得到了%s",killer->name(1),name,str);
        str+="。";
        killer->add_temp("ymdh/yaomokilled",1);
        announce(str);
}

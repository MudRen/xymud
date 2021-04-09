#include <ansi.h>
inherit "/d/maze/beiyin/room.c";

string look_bagua();

mixed *quest = ({
	({
		4,9,2,
		3,5,7,					
		8,1,6,
	}),
	({
		2,9,4,
		7,5,3,							
		6,1,8,
	}),
	({
		8,1,6,
		3,5,7,
		4,9,2,
	}),
	({
		6,1,8, 
   		7,5,3, 
   		2,9,4,
   	}),
});	 

void create() 
{ 
        set("short", "三花堂"); 
        set("long", @LONG 
三花堂是城中名声恶劣的一个帮会，堂中的人大多是些亡命之徒，
烧杀抢劫，欺压百姓，无恶不做。而官府却很难抓到把柄而将其除之。
据说帮中好多头目乃是从西域学得的奇技异能，杀人于无形之中。
    如今堂中了无人迹，但是你隐隐约约感觉到一丝丝杀机。在三张虎
皮大椅之前，屋子的正中立着一杆黑黝黝的铁柱，上面血迹斑斓，柱子
的正中挂着一个铁八卦(bagua)。
LONG
); 
	set("item_desc",([
		"bagua" : (: look_bagua :),
	]));
	set("alternative_die",1);
	set("virtual_room",1);	
        setup();
} 

string num_string(int v)
{
	mapping ns = ([
		1 : "１",	2 : "２",	3 : "３",
		4 : "４",	5 : "５",	6 : "６",
		7 : "７",	8 : "８",	9 : "９",
	]);
	if( undefinedp(ns[v]) )
		return 0;
	return ns[v];	
}

void create_quest()
{
	string str,arg;
	int *qq,*t1,*t2,*t3,i;
	int n1,n2,n3;
	if( query_temp("newbie_quest_msg") 
	 || query_temp("boss_killed") 
	 || query_temp("pushed") )
		return;
	qq = quest[random(sizeof(quest))];
	if( !qq )
		return;
	
	t1 = ({ qq[0],qq[1],qq[2],});
	t2 = ({ qq[3],qq[4],qq[5],});
	t3 = ({ qq[6],qq[7],qq[8],});
	
	n1 = t1[random(sizeof(t1))];
	n2 = t2[random(sizeof(t2))];			
	n3 = t3[random(sizeof(t3))];

	arg = "\t\t\t┌─┬─┬─┐  \n\t\t\t│";
	for(i=0;i<sizeof(t1);i++)
	{
		if( t1[i]!=n1 )
			arg+= "█│";
		else	arg+= num_string(t1[i])+"│";
	}
	arg+= "\n\t\t\t├─┼─┼─┤\n\t\t\t│";
	for(i=0;i<sizeof(t2);i++)
	{
		if( t2[i]!=n2 )
			arg+= "█│";
		else	arg+= num_string(t2[i])+"│";
	}
	arg+= "\n\t\t\t├─┼─┼─┤\n\t\t\t│";
	for(i=0;i<sizeof(t3);i++)
	{
		if( t3[i]!=n3 )
			arg+= "█│";
		else	arg+= num_string(t3[i])+"│";
	}
	arg+= "\n\t\t\t└─┴─┴─┘\n";
	
	arg = "◎九宫图\n\t将下面图中的数字补全，使横竖斜每个方向相加均为十五之数，\n\t其后，乃将补全之数按从左至右，从上而下方向顺序排列。\n\t最后，在铁八卦上按下(push)所得的数字，即打开三花宝库。\n"+arg;
	set_temp("newbie_quest_msg",arg);			
		
	str = "";
	for(i=0;i<sizeof(qq);i++)
	{
		if( qq[i]==n1 || qq[i]==n2 ||  qq[i]==n3 )
			continue;
		str+= ""+qq[i]+"";
	}
	set("answer",str);
}					

string look_bagua()
{
	object me = this_player();
	if( !userp(me) )
		return 0;
	if( query_temp("boss_killed") )
		return "密室已开，多留无益。\n";		
	if( query_temp("newbie_quest_msg") )
		return query_temp("newbie_quest_msg");
	create_quest();
	return query_temp("newbie_quest_msg");
}
	
void init()
{
	add_action("do_push","push");
}

int do_push(string arg)
{
	object npc, *team,me = this_player();
	
	if( !arg || !query_temp("newbie_quest_msg")   	//无谜题
	 || query_temp("boss_killed") 			//boss已杀
	 || query_temp("pushed") )			//已破解
		return 0;

	if( me->is_fighting() )
	{
		write("专心战斗吧。\n");
		return 1;
	}
	
	if( me->is_busy() )
	{
		write("你现在正忙着呢。\n");
		return 1;
	}
	
	team = me->query_team();
	if( team && !me->is_team_leader() )
	{
		write("必须由队长来破解。\n");
		return 1;
	}
	
	me->start_busy(3);
	message_vision("$N上前一步，在铁八卦上按下了"+arg+"。\n",me);
	set_temp("pushed",1);
	if( arg!=query("answer") )
	{
		message_vision("\n铁八卦顿时炸的粉碎。\n\n",me);
		set("item_desc",([
			"bagua" : "破碎的铁八卦。\n",
		]));	
		set_temp("newbie_quest_msg","破碎的铁八卦。\n");
		tell_object(me,HIR"【副本】你按错了机关，看来本回合是无法为民除害了。"NOR"\n");
		return 1;
	}
	
        npc = new("/d/maze/beiyin/npc/eba");
	if( npc->move(this_object()) )
		npc->command("say 哪个不要命的"+RANK_D->query_rude(me)+"，居然敢打你家爷爷的主意？！拿命来！\n");
	else	message_vision("\n结果什么反应也没有，看来此处是个假宝库。\n",me);
	return 1;
}	
		
	
	

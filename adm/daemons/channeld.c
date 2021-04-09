// channeld.c
// Modify by Jingxue for XYCQ 6.10.2003
// Modify by Qiushui for TSRJ 1.30.2004
#include <ansi.h>
inherit F_DBASE;

#define REMOTE_Q    "/adm/daemons/network/services/gemote_q.c"
        
mapping channels = ([
        "sys":  ([      
                "msg_speak"     : NOR HIR "【系统】"+BLK"%s：%s\n" NOR, 
                "wiz_only"      : 1, 
                "msg_color"         : NOR HIR BLK,
                ]),
        "wiz":  ([      
                "msg_speak"     : NOR HIW "【巫师】%s：%s\n" NOR,
                "msg_emote"     : NOR HIW "【巫师】%s\n" NOR,
                "wiz_only"      : 1,
                "msg_color"         : NOR HIW,
                ]),
        "xyj":  ([      
                "msg_speak"     : NOR HIR "【西游记】%s"NOR HIR"：%s\n" NOR,
                "msg_emote"     : NOR HIR "【西游记】%s\n" NOR,
//                "intermud"      : GCHANNEL, 
                "channel"       : "xyj",
//                "filter"        : (:$1["MUDLIB"]=="A Journey to the West" :) ,
                "msg_color"         : NOR HIR,
                ]),
        "es":   ([  
                "msg_speak"     : NOR WHT "【千里传音】%s"NOR WHT"：%s\n" NOR,
                "msg_emote"     : NOR WHT "【千里传音】%s\n" NOR,
//                "intermud"      : GCHANNEL, 
                "channel"       : "es",
                "filter"        : 1,
                "msg_color"         : NOR WHT,
                ]), //keep the channel name as "es" to be compatible with other ES2 type muds.
        "sldh": ([      
                "msg_speak"     : NOR HIW "【水陆大会】%s"NOR HIW"：%s\n" NOR,
                "msg_emote"     : NOR HIW "【水陆大会】%s\n" NOR,
                "msg_color"         : NOR HIW,
                ]),
        "chat": ([      
                "msg_speak"     : NOR HIC "【谈天说地】%s"NOR HIC"：%s\n" NOR,
                "msg_emote"     : NOR HIC "【谈天说地】%s\n" NOR,
                "msg_color"         : NOR HIC,
                ]),
        "job": ([      
                "msg_speak"     : NOR HIG "【任务】%s"NOR HIG"：%s\n" NOR,
                "msg_emote"     : NOR HIG "【任务】%s\n" NOR,
//                "anonymous"     : "传说",
                "msg_color"         : NOR HIG,
                ]),
        "rumor":([      
                "msg_speak"     : NOR HIM "【小道消息】%s"NOR HIM"：%s\n" NOR,
                "msg_emote"     : NOR HIM "【小道消息】%s\n" NOR,
                "msg_color"         : NOR+HIM,
                "anonymous"     : "某人",
                ]),
        "music":([      
                "msg_speak"     : NOR HIM"【心笙乐府】%s"NOR HIM"唱着：%s\n" NOR,
                "msg_color"         : NOR HIM,
                ]),
        "club":([  
                "msg_speak"     : NOR HIW "【帮派】%s"NOR HIW"：%s\n" NOR,
                "msg_emote"     : NOR HIW "【帮派】%s" NOR,
                "msg_color"         : NOR HIW,
                "bh_only"    : 1, 
                ]), 
        "mp":([  
                "msg_speak"     : NOR HIG "【门派】%s"NOR HIG": %s\n" NOR,
                "msg_emote"     : NOR HIG "【门派】%s" NOR,
                "msg_color"         : NOR HIG,
                "menpai_only"   : 1,
                ]),
]);

string chan_infor,party,menpai;
string cs,faction;
void add_rumor(object me,string msg);

int can_chat( string sArg ) //允许说话?
{
	return 1 ;
}

mapping query_channels(){ return channels; }

void create()
{
	seteuid(getuid());      // This is required to pass intermud access check.
	set("channel_id", "频道精灵");
	this_object()->set("rumor_point",0);
}

varargs int do_channel(object me, string verb, string arg, int emote,int allow_chat)
{
	object *ob;
	string *tuned_ch, who, arg1, color,arg2;
	int time,count,count1,last_chat,len;

	if( sizeof(verb)>0 )
        {
        	if( verb[sizeof(verb)-1] == '*' ) 
                {
                	emote = 1;
                	verb = verb[0..<2];
                }
        }
	if( arg && strlen(arg)>240 ) 
        	return 0;
	if( !mapp(channels) || undefinedp(channels[verb]) )
        	return 0;
	if( !wizardp(me) && arg && !can_chat(arg) )
        	return 0 ;
	if( userp(me) && channels[verb]["sys_only"] && !wizardp(me) )
        	return 0;       
	if( channels[verb]["system_msg"] )
        {
        	if( !userp(me) )
                {
                	party = me->query("system_msg");
                	if( party && stringp(party) )
                        	channels[verb]["msg_speak"] = NOR HIC"【"+party+NOR HIC"】%s：%s\n" NOR;
		} 
	}	      
	if( !allow_chat ) 
        {
        	if( channels[verb]["wiz_only"] && !wizardp(me) && userp(me) )
                	return 0;
		if( channels[verb]["bh_only"] )
                {
               		if( !me->query("banghui") )
                       		return notify_fail("你还是先加入一个帮派再说吧。\n");
               	}
       		if( channels[verb]["menpai_only"] )
               	{
               		if( !me->query("family/family_name") )
                       		return notify_fail("你是哪个门派的。\n");
               	}
        	if( emote && undefinedp(channels[verb]["msg_emote"])  ) 
               		return notify_fail("对不起，这个频道不支持 emote 。\n");
	
        	time=time();
        	if( me->query("channel/chat_block") && (time-me->query("channel/chat_block"))<0 )
                	return notify_fail("你的交谈频道被暂时关闭了。\n");
        	count=me->query("channel/chat_count");
        	count1=sizeof(explode(" "+arg,"\n"))/3+1;
        	count1+=sizeof(arg)/200;
        	count+=count1;
        	last_chat=me->query("channel/last_chat");
        	if(count>2) 
                {
                	count=0;
                	me->set("channel/last_chat",time);
                	if(time==last_chat || count1>2) 
                        {
                        	me->set("channel/chat_block",time+180);
                        		return notify_fail("因为一次讲话太多，你的交谈频道被暂时关闭了。\n");
                        }
                }
        	me->set("channel/chat_count",count);
        	arg2 = me->query_temp("last_channel_msg");
        	if( !arg2 )
                	arg2 = "...";
        	if( arg && COLOR_D->clean_color(arg)==COLOR_D->clean_color(arg2) )     
                	return notify_fail("用交谈频道说话请不要重复相同的讯息。\n");

        	tuned_ch = me->query("channels");
        	if( !pointerp(tuned_ch) )
                	me->set("channels", ({ verb }) );
        	else if( member_array(verb, tuned_ch)==-1 )
                	me->set("channels", tuned_ch + ({ verb }) );

	        if( emote && !channels[verb]["intermud_emote"]) 
                {
        	        string vb, emote_arg;
                		notify_fail("本站目前并没有 "+arg+" 这个Emote。\n");
                	if( nullp(arg) ) return 0;
                	if( sscanf(arg, "%s %s", vb, emote_arg)!= 2 ) 
                        {
                        	vb = arg;
	                        emote_arg = "";
        		}
                	color=channels[verb]["msg_color"];
                	if( channels[verb]["anonymous"] )
				arg = EMOTE_D->do_emote(me, vb, emote_arg, color, 1, 1);
                	else    
                	{
                        	arg = EMOTE_D->do_emote(me, vb, emote_arg, color, 1, 0,!undefinedp(channels[verb]["intermud"]));
                        	if( !arg ) 
                                {
                                	string id, site;
	                                if( sscanf(emote_arg, "%s@%s", id, site)==2) 
                                        {
        	                                int age = me->query("mud_age");
                	                        if( !wizardp(me) ) 
                        			{
                                                	if( age<3600 ) 
                                                        	return notify_fail("你现在还不能使用这个频道。\n");
	                                                else if( age<86400 ) 
                                                        {
        	                                                if( me->query("sen")<30 ) 
                	                                                return notify_fail ("你现在精神不足，不能使用这个频道。\n");
                        	                                me->receive_damage("sen",10);
                                                        }
                                                }
                                        	REMOTE_Q->send_msg(channels[verb]["channel"], me,vb, id, site, channels[verb]["filter"]);
                                        	return 1;
                                        }
                                }
                        }
                	if( !arg )     return 0;
                }
        }

	if( channels[verb]["system_msg"] )
        {
        	if( userp(me) ) who = channels[verb]["system_msg"];
        	else    who = COLOR_D->clean_color(me->name());
        }
	else if( channels[verb]["anonymous"] ) 
        {
        	who = channels[verb]["anonymous"];
        	if( userp(me) ) 
                {
                	if( me->query("sen")<50 )  
                        	return notify_fail("你已经没有精神散布谣言了。\n");
                	me->receive_damage("sen",10);
                	do_channel( this_object(), "sys", sprintf("谣言：%s(%s)。", me->name(1),me->query("id")));
                }
        }
	else if( userp(me) || !stringp(who = me->query("channel_id")) ) 
        {
        	who = me->query("name");
        	if( me->query("id") ) 
                	who+= "(" + capitalize(me->query("id")) + ")";
        }

	ob = filter_array( users(), "filter_listener", this_object(), channels[verb] );
	if( !arg ) arg = "．．．";
	len = strlen(arg);
	while(len>1 && arg[len-1]=='\n')
        	arg = arg[0..((len--)-2)];
        //remove excessive return at the end. by mon 9/20/97
	if( wizardp(me) )        
		arg = COLOR_D->replace_color(arg,1);
	if( userp(me) ) 
        	arg1 = replace_string(arg, "$N", me->name());
	else    arg1 = arg;

	if( emote ) 
        {
        	if( channels[verb]["intermud_emote"] ) 
	                arg1 = who + " " + arg;
        }
	if( arrayp(channels[verb]["extra_listener"]) ) 
        {
        	channels[verb]["extra_listener"] -= ({ 0 });
        	if( sizeof(channels[verb]["extra_listener"]) )
                	channels[verb]["extra_listener"]->relay_channel(me, verb, arg);
        }
	if( !undefinedp(channels[verb]["intermud"])
   	 && base_name(me)!=channels[verb]["intermud"] ) 
	{
        	if( userp(me) ) 
                {
                	int age = me->query("mud_age");
//                arg = replace_string(arg, "$N", me->name()+"("+capitalize(me->query("id"))+"@"+Mud_name()+")",1);
                	arg = replace_string(arg, "$N", me->name());
                	if( !wizardp(me) ) 
                        {
                        	if( age<3600 ) 
                                	return notify_fail("你现在还不能使用这个频道。\n");
                        	else if( age<86400 ) 
                                {
                                	if( me->query("sen")<30 ) 
                                        	return notify_fail("你现在精神不足，不能使用这个频道。\n");
                                	me->receive_damage("sen",10);
                                }
                        }
                }
        	channels[verb]["intermud"]->send_msg(channels[verb]["channel"], me->query("id"), me->name(1), arg, emote, channels[verb]["filter"] );
        }

	if( emote ) 
        	message( "channel:" + verb,sprintf( channels[verb]["msg_emote"], arg1 ), ob );
	else    message( "channel:" + verb,sprintf( channels[verb]["msg_speak"], who, arg1 ), ob );

	if( userp(me) ) 
        	me->set_temp("last_channel_msg", arg);
	if( channels[verb]["anonymous"] ) 
        	add_rumor(me,arg); 
	return 1;
}

int filter_listener(object ppl, mapping ch)
{
	if( !environment(ppl) ) return 0;
	if( ch["wiz_only"] ) return wizardp(ppl);
	if( ch["bh_only"] )
        	return ( wizardp(ppl)&& (!ppl->query("env/bh") || ppl->query("env/bh")==party))|| party == ppl->query("banghui/banghui"); 
	if( ch["menpai_only"] )
        	return ( wizardp(ppl)|| ppl->query("family/family_name")==menpai); 
	return 1;
}

void register_relay_channel(string channel)
{
	object ob;

	ob = previous_object();
	if( undefinedp(channels[channel]) || !ob ) return;
	if( arrayp(channels[channel]["extra_listener"]) ) 
        {
        	if( member_array(ob, channels[channel]["extra_listener"]) >=0 ) 
                	return;
        	channels[channel]["extra_listener"] += ({ ob });
        } 
	else    channels[channel]["extra_listener"] = ({ ob });
}

void add_rumor(object me,string msg)
{
	object ob = this_object();
	string msg_id;
	int i;
	int detect_chance;
	int rumor_point = ob->query("rumor_point");
	rumor_point++;
	if( rumor_point>20 ) 
        	rumor_point-=20;

	msg_id = "rumor_msg_0";
	i = sizeof(msg_id);
	msg_id[i-1]=msg_id[i-1]+ rumor_point;
	ob->set(msg_id,msg);

	detect_chance = 31-(int)(me->query("daoxing")/33333);
	if( !userp(me) || wizardp(me) || random(100)>detect_chance )
        {
        	ob->set(msg_id,"none");
	        return;
        }
	ob->set(msg_id,me->query("name")+"("+me->query("id")+")");
	return;                 
}

string query_rumor_msg(int num)
{
	string msg_id;
	string msg;
	int i;
	msg_id = "rumor_msg_0";
	i = sizeof(msg_id);
	msg_id[i-i]= msg_id[i-i]+num;
	return this_object()->query(msg_id);
}

string query_rumor_id(int num)
{
	string msg_id;
	string msg;
	int i;
	msg_id="rumor_id_0";
	i = sizeof(msg_id);
	msg_id[i-i]= msg_id[i-i]+num;
	return this_object()->query(msg_id);
}
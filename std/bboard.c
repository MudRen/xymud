// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
// modified by bear
// bboard.c
#include <ansi.h>

#define BOARD_CAPACITY query("capacity")
string query_master();
//string *color=({"GRN","RED","HIR","HIG","HIB","HIC","HIM","HIW","HIY"});

inherit ITEM;
inherit F_SAVE;

void setup()
{
    string loc;

    if( stringp(loc = query("location")) )
            move(loc);
    set("no_get", 1);
    seteuid(getuid());
    restore();
}

void init()
{
        if(this_player()->visible(this_object())) 
        {
        add_action("do_post", "post");
        add_action("do_re","re");
        add_action("do_read", "read");
        add_action("do_discard", "discard");
        add_action("do_document", "document");
        add_action("do_appoint","appoint");
        add_action("do_demit","demit");
        }
}

string query_save_file()
{
    string id;
    if( !stringp(id = query("board_id")) ) return 0;
    return DATA_DIR + "board/" + id;
}

string short()
{
   mapping *notes;
   int i, unread, last_read_time;

   notes = query("notes");
   if( !pointerp(notes) || !sizeof(notes) )
     return ::short() + " [ 没有任何留言  本板板主："+HIY+query_master()+NOR+"]";

   if( this_player() ) {
     last_read_time = (int)this_player()->query("board_last_read/" + (string)query("board_id"));
     for(unread = 0, i=sizeof(notes)-1; i>=0; i--, unread ++)
        if( notes[i]["time"] <= last_read_time ) break;
   }
   if( unread )
     return sprintf("%s [ %d 张留言，%d 张未读  本板板主："+HIY+query_master()+NOR+"]", ::short(), sizeof(notes), unread);
   else
     return sprintf("%s [ %d 张留言  本板板主："+HIY+query_master()+NOR+"]", ::short(), sizeof(notes));
}

string query_master()
{
        if( query("master") )
                return query("master");
        else    return "空缺";
}

string long()
{
   mapping *notes;
   int i, last_time_read;
   string msg, myid;

   notes = query("notes");
   msg=sprintf("版主：%-10s              %-20s                        \n",
                query_master(),query("name"));

   if( !pointerp(notes) || !sizeof(notes) ) return query("long");

   last_time_read = this_player()->query("board_last_read/" + (string)query("board_id"));

   for(i=sizeof(notes)-1; i>=0; i--)
     msg += sprintf("%3d %s %s %-25s %s %s\n",
        i+1, ( notes[i]["time"] > last_time_read ? "N": " "),
       ctime(notes[i]["time"])[4..9],notes[i]["author"], notes[i]["sx"],
notes[i]["title"]);
msg+= HIY"欢迎光临小雨西游                             本站地址："HIR"61.178.245.56 8888\n"NOR;

   return msg;
}

string hostname(object ob)
{
        ob = this_player();

        if( ob->query_host_name() )
        {
                if( ob->query("env/hostname") )
                return ob->query("env/hostname")+ob->query_host_name();
                return ob->query_host_name();
        }

        else
        {
                if( ob->query("env/hostname") )
                return ob->query("env/hostname")+".XYCQ.net";
                return ob->query("id")+".XYCQ.net";
        }
}

// This is the callback function to process the string returned from the
// editor defined in F_EDIT of player object.

void done_post(object me, mapping note, string text)
{
    mapping *notes;
    if( !text ) text = "";
    if( this_player()->query_temp("last_repost_msg") )
        {
            text = sprintf(this_player()->query_temp("last_repost_msg"),text);
                this_player()->delete_temp("last_repost_msg");
    }
    note["msg"] = text;
    note["time"] = time();
    notes = query("notes");
    if( !pointerp(notes) || !sizeof(notes) )
            notes = ({ note });
    else    notes += ({ note });

    // Truncate the notes if maximum capacity exceeded.
    if( sizeof(notes) > BOARD_CAPACITY )
            notes = notes[BOARD_CAPACITY / 5 .. BOARD_CAPACITY];
    set("notes", notes);
    tell_object(me, "留言完毕。\n");
    me->delete_temp("BBS_POST");
    save();
    return;
}

int do_post(string arg)
{
    mapping note;
    object me = this_player();
    if(!wizardp(me) && environment(me)->query("post_limit"))
            return notify_fail("只有巫师才可以在这里留言。\n");
    if(!arg) return notify_fail("留言请指定一个标题。\n");
    if(strlen(arg) > 20 ) return notify_fail("标题太长！\n");
   
    note = allocate_mapping(5);
    note["title"] = arg;
    note["sx"] = "◆";
    note["author"] = this_player()->query("name")+"("+capitalize(this_player()->query("id"))+")";
    note["time"] = time();
    note["ip"] = hostname(this_player());
    me->set_temp("BBS_POST",1);
    this_player()->edit( (: done_post, this_player(), note :) );
    return 1;
}

int do_re(string arg)
{
    int i;
    mapping note;
        object me;
    string arg1,mm,*mms;
    mapping *notes;
    notes=query("notes");

    me = this_player();
    if(!wizardp(me) && environment(me)->query("post_limit"))
            return notify_fail("只有巫师才可以在这里留言。\n");
    if(!arg) return notify_fail("你要Re哪篇文章？\n");
    if( arg=="up" )  arg = sprintf("%d",(sizeof(notes)));
    if(!intp(atoi(arg)) || atoi(arg)<=0 ) return notify_fail("你只能Re具体的哪一篇文章，用re 数字表示\n");
    if(atoi(arg) > sizeof(notes) ) return notify_fail("没有这篇文章！\n");

    note = allocate_mapping(5);
    if( notes[atoi(arg)-1]["RE"] )   
        return notify_fail("你不能递嵌回答，请用Post命令。\n");
    note["title"] = "Re 第"+arg+"楼";
    note["RE"] = 1;
    note["author"] = this_player()->query("name")+"("+capitalize(this_player()->query("id"))+")";
    note["time"] = time();
    note["sx"] = HIR"Re"NOR;
    note["ip"] = hostname(this_player());
    
    mm = notes[atoi(arg)-1]["msg"];
    if( !mm || !stringp(mm) )
        return notify_fail("出错了？！\n");
    mms = explode(mm,"\n");
    arg = NOR CYN"──────────────引用──────────────\n"NOR;
    
    for(i=0;i<sizeof(mms);i++)
        arg+= "     "+mms[i]+"\n";
    arg+= NOR CYN"──────────────────────────────\n"NOR+"%s"+HIG"\n                              By "+capitalize(this_player()->query("id"))+"\n"NOR;
    this_player()->set_temp("last_repost_msg",arg);
    me->set_temp("BBS_POST",1);
    this_player()->edit( (: done_post, this_player(), note :) );
    return 1;
}

int do_appoint(string arg)
{
        object me = this_player();

    if( (string)SECURITY_D->get_status(this_player(1)) != "(admin)"
         && (string)SECURITY_D->get_status(this_player(1)) !="(arch)"
         && (string)SECURITY_D->get_status(this_player(1)) !="(wizard)" )
            return notify_fail("你没有任免版主的权利!\n");
        if( !arg)
            return notify_fail("你要任免谁为本版版主？\n");
    if( !present(arg,environment(me) ) )
            return notify_fail("你要任命的玩家不在这个地方！\n");
    if(this_object()->query("master") )
            return notify_fail("这个版已经有版主了！\n");
    this_object()->set("master",arg);
        message("system",HIR"【公告】：任命 "+arg+" 为"+this_object()->name()+"板主！\n"NOR,users());
        save();      
    return 1;
}

int do_demit()
{
        object me = this_player();

    if( (string)SECURITY_D->get_status(this_player(1)) != "(admin)"
         && (string)SECURITY_D->get_status(this_player(1)) !="(arch)"
         && (string)SECURITY_D->get_status(this_player(1)) !="(wizard)" )
            return notify_fail("你没有任免版主的权利!\n");
    if(!this_object()->query("master") )
            return notify_fail("这个版本来就没有版主！\n");
        message("system",HIR"【公告】：罢免"+this_object()->name()+"板主 "+ this_object()->query("master") +" ！\n"NOR,users());
        this_object()->delete("master");
        save();
    return 1;
}
    
int do_read(string arg)
{
    int num,i;
    mapping *notes, last_read_time;
    string myid,msg,mm,*mms;

    last_read_time = this_player()->query("board_last_read");
    myid = query("board_id");
    notes = query("notes");

    if( !pointerp(notes) || !sizeof(notes) )
            return notify_fail("留言板上目前没有任何留言。\n");
    if( !arg ) return notify_fail("指令格式：read <留言编号>|new|next\n");
    if( arg=="new" || arg=="next" ) 
    {
            if( !mapp(last_read_time) || undefinedp(last_read_time[myid]) )
                num = 1;
            else    
                for(num = 1; num<=sizeof(notes); num++)
                    if( notes[num-1]["time"] > last_read_time[myid] ) break;
    } 
    else if( !sscanf(arg, "%d", num) )
            return notify_fail("你要读第几张留言？\n");

    if( num < 1 || num > sizeof(notes) )
            return notify_fail("没有这张留言。\n");
    num--;

    
this_player()->start_more( sprintf(
"  作者  %-20s                      讨论区  %20s
  标题  %-70s
  时间  %-70s  \n------------------------------------------------------------------------------\n\n\n",
notes[num]["author"],name(),notes[num]["title"],XYJTIME_D->chinese_time(notes[num]["time"]))
+ COLOR_D->replace_color(notes[num]["msg"],1) +
sprintf("\n\n\n※ Origin : 小雨西游站 < 61.178.245.56 8888 >
⊙ From : %-70s", notes[num]["ip"]));

    if( !mapp(last_read_time) )
            this_player()->set("board_last_read", ([ myid: notes[num]["time"] ]) );
    else if( undefinedp(last_read_time[myid]) || notes[num]["time"] > last_read_time[myid] )
                last_read_time[myid] = notes[num]["time"];
    return 1;
}

int do_discard(string arg)
{
    mapping *notes;
    int num;

    if( !arg || sscanf(arg, "%d", num)!=1 )
            return notify_fail("指令格式：discard <留言编号>\n");
    notes = query("notes");
    if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
            return notify_fail("没有这张留言。\n");
    num--;
    if( notes[num]["author"] != (string) this_player(1)->query("name")+"("+capitalize(this_player(1)->query("id"))+")"
     && (string)SECURITY_D->get_status(this_player(1)) !="(arch)"
     && (string)SECURITY_D->get_status(this_player(1)) != "(admin)" 
     && this_object()->query("master") != this_player(1)->query("id") )
        return notify_fail("你无权删除这个留言！\n");
    if(num >0)
            notes = notes[0..num-1] + notes[num+1..sizeof(notes)-1];
        else    notes =notes[num+1..sizeof(notes)-1];
    set("notes", notes);
    save();
    write("删除第 " + (num+1) + " 号留言....Ok。\n");
    return 1;
}


int do_document(string arg)
{
        object document, content, cont_num;
    string mon, dirname="/data/";
    int month, num, nummonth, defmon, defyear, argn;
        mapping *notes;
    string *strmon=({"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"});

    if( (string)SECURITY_D->get_status(this_player(1)) != "(admin)"
     && (string)SECURITY_D->get_status(this_player(1)) !="(arch)" 
     && (string)SECURITY_D->get_status(this_player(1)) !="(wizard)" )
            return notify_fail("你没有存档的权力！\n");
    //snowtu
    if( !arg )  return notify_fail("内容为空!\n");
//by mon. 9/6/97
        if(environment(this_player())->query("wiz_board"))
            dirname+="wiz_doc/";
        else    dirname+="doc/";
    argn=sscanf(arg, "%d %d %d", num, defmon, defyear);

        if(!arg || argn >3)
                return notify_fail("指令格式：document <留言编号>\n");
    if(argn==3) 
    {
            dirname = dirname + sprintf("%d",defyear)+"/";
            month=defmon;
            mon="Null";
        }
    if(argn==2) 
    {
            if(defmon>1995) 
            {
                dirname = dirname + sprintf("%d",defmon)+"/";    
                mon=ctime(time())[4..6];
            }
            else 
            {
                dirname = dirname + ctime(time())[20..23] + "/";
                month=defmon;
                mon="Null";
            }
        }
    if(argn==1) 
    {
            dirname = dirname + ctime(time())[20..23] + "/";
            mon=ctime(time())[4..6];
        }
    if( mon=="Null" ) 
    {
            if(month>12 || month<1) return notify_fail("要存的月份不存在！\n");
            mon=strmon[month-1];
        }
    else switch (mon) 
    {
            case "Jan": month=1; break;
        case "Feb": month=2; break;
                case "Mar": month=3; break;
                case "Apr": month=4; break;
                case "May": month=5; break;
                case "Jun": month=6; break;
                case "Jul": month=7; break;
                case "Aug": month=8; break;
                case "Sep": month=9; break;
                case "Oct": month=10; break;
                case "Nov": month=11; break;
                case "Dec": month=12; break;
                default : return notify_fail("要存的月份不存在！\n");
        }
    if(month>12 || month<1) return notify_fail("要存的月份不存在！\n");
    notes = query("notes");
    if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
            return notify_fail("没有这张留言。\n");
    num--;
    cont_num=new("/obj/not.c");
    if( !cont_num )
        return notify_fail("木有/obj/not.c这个文件\n");
    cont_num->set("file_name", dirname+"month.number");
        cont_num->restore();
    if(!objectp(cont_num) )
    {
        destruct(cont_num);
                return notify_fail("文档读取失败！\n");
    }  
    nummonth=cont_num->query(mon);
    nummonth++;
    cont_num->set(mon, nummonth);
    if(!cont_num->save())
    {
        destruct(cont_num);
            return notify_fail("存档失败！\n");
        }   
    content=new("/obj/not.c");
    content->set("file_name", dirname+"content."+mon);
    content->restore();
    if( !objectp(content) )
    {
        destruct(content);
            return notify_fail("文档读取失败！\n");
        }   
    if(content->query("msg")) 
        content->set("msg", content->query("msg")+ sprintf("[%3d] %-40s %12s (%s)\n",nummonth, notes[num]["title"], notes[num]["author"], ctime(notes[num]["time"])[0..9]));
    else    content->set("msg", sprintf("[%3d] %-40s %12s (%s)\n",nummonth, notes[num]["title"], notes[num]["author"], ctime(notes[num]["time"])[0..9]));
    if(!content->save())
    {
        destruct(content);
                return notify_fail("存档失败！\n");
    }                
    document=new("/obj/not.c");
    document->set("file_name", dirname+ sprintf("%s/doc%d.%d",mon,month, nummonth) );
    document->restore();
    if( !objectp(document) )
    {
        destruct(document);
            return notify_fail("文档读取失败！");
        }
    document->set("msg",
sprintf("[%3d] %-40s %12s (%s)\n────────────────────────────────────────\n", nummonth, notes[num]["title"], notes[num]["author"], ctime(notes[num]["time"])[0..9])
+ notes[num]["msg"]
);
    if(!document->save())
    {
        destruct(document);     
            return notify_fail("存档失败！\n");
        }
    write("OK.\n");
   
/*
   if(num >0)
             notes = notes[0..num-1] + notes[num+1..sizeof(notes)-1];
        else
          notes =notes[num+1..sizeof(notes)-1];
        set("notes", notes);
        save();
*/
    if( cont_num ) destruct(cont_num);
    if( content ) destruct(content);
    if( document ) destruct(document);
    return 1;
}   


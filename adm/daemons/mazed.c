#include <ansi.h>
#include "/cmds/std/valid_move.h"
inherit F_DBASE;

#define MAZE            "maze.c"
#define ENTRY           "enter.c"
#define EXIT            "out.c"
#define MAZE_DIR        "/d/maze/"
#define MAZE_DATA       "/data/maze/"  

#define DEST_TIME       10800   // 3小时后销毁
#define REMOVE_TIME     10800   // 60 分钟后

int clean_up() { return 1; }

nosave object *total = ({ });
object *query_total() { return total; }
int remove_maze(object me, string arg);
protected void init_player(object me);
protected void restore_status(object me);
protected void auto_check();
int check_out(object me);
int check_quit(object me);

string query_maze_file(string x, string y)
{
        return sprintf(MAZE_DATA + "%s/%s/", x, y);
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "迷宫精灵");
        CHANNEL_D->do_channel(this_object(), "sys", "迷宫系统已经启动。");
}

int notify_fails(string arg)
{
        write(arg);
        return 0;
}

protected mixed create_maze(object me, string maze)
{
        string src, dst,id;
        string filename;

        if( !me || !objectp(me) )
                return 0;

        id = sprintf("%c/%s",me->query("id")[0],me->query("id"));
        src = MAZE_DIR + maze + "/" + MAZE;
        if( !me->query_temp("maze/公共地图") )
                dst = query_maze_file(id, maze) + MAZE;
        else    dst = query_maze_file(me->query_temp("maze/公共地图"), maze) + MAZE;                   
        assure_file(dst);
        cp(src, dst);
        
        src = MAZE_DIR + maze + "/" + ENTRY;
        if( !me->query_temp("maze/公共地图") )
                dst = query_maze_file(id, maze) + ENTRY;
        else    dst = query_maze_file(me->query_temp("maze/公共地图"), maze) + ENTRY;                  
        filename = dst;
        cp(src, dst);
        
        src = MAZE_DIR + maze + "/" + EXIT;
        if( !me->query_temp("maze/公共地图") )
                dst = query_maze_file(id, maze) + EXIT;
        else    dst = query_maze_file(me->query_temp("maze/公共地图"), maze) + EXIT;   
        cp(src, dst);
        me->set_temp("maze_dir",maze);
        return filename;
}

int enter_maze(object me, string arg) 
{
        string efile, mfile;
        object *member, ob;
        object *inv, obj;
        string id,fid;
        int i,s,pblk=0;
        
        if( me->query_condition("killer") )
                return notify_fails("杀人通缉犯是不能进入副本的。\n");
        if( !valid_move(me) )
                return notify_fails("你目前动弹不得，不能进入该地图。\n");
        if( !wizardp(me) && time() - me->query("maze/"+arg)<1800 )
                return notify_fails("同一个副本半小时内不能反复创建。\n");
        inv = deep_inventory(me);
        if( inv && sizeof(inv) > 0 )
        {
                foreach( obj in inv ) 
                if( obj && obj->is_character() ) 
                        return notify_fails("不可以将其他角色或者NPC通过背的方式带进副本内。\n");
        }
        //系统任务组成的大迷宫
        if( me->query_temp("maze/公共地图") )
        {
                id = me->query_temp("maze/公共地图");
                pblk = 1;
        }
        else
        {       
                //组队        
                if( pointerp(member = me->query_team()) && sizeof(member)>0 )
                        if( me->query_leader() )  id = (me->query_leader())->query("id");
                        else  return notify_fail("你的队长呢？\n");
                else    id = me->query("id");
        }
        if( !id )
                return notify_fails("获取不到创建副本的ID。\n");
        fid = sprintf("%c/%s",id[0],id);                
        if( me->query_temp("maze/公共地图") ) fid = id;
        efile = query_maze_file(fid, arg) + ENTRY;
        mfile = query_maze_file(fid, arg) + MAZE; 
        // 已经创建过
        if( file_size(efile) > 0 )
        {
                if( !ob = find_object(efile) )
                {                        
                        if( !ob = load_object(efile) )
                                return notify_fails("读取副本失败，请告之当值巫师。\n");
                        obj = get_object(mfile);
                        if( (obj->query_remove_time())<=0 )
                                REMOVE_D->add_room(obj,DEST_TIME);
                }
        }
        else // 没有创建过      
        {  
                if( id!=me->query("id") && pblk==0 )
                        return notify_fails("必须由队长"+id+"来进入该地图。\n");                
                efile = create_maze(me, arg); 
                if( !efile )
                        return notify_fails("创建副本第一步失败，请告之当值巫师。\n");
                ob = get_object(efile);
                if( !ob || !objectp(ob) )
                        return notify_fails("创建副本第二步失败，请告之当值巫师。\n");
                mfile = query_maze_file(fid, arg) + MAZE; 
                obj = get_object(mfile);
                if( !obj )
                        return notify_fails("创建副本第三步失败，请告之当值巫师。\n");
                if( (obj->query_remove_time())<=0 )
                        REMOVE_D->add_room(obj,DEST_TIME);
        }
        if( !arrayp(total) )
                total = ({ me });
        else if( member_array(me, total) == -1 )
                total += ({ me });
        if( pblk==0 )                
        {
                me->set("maze/"+arg,time());                        
                me->set_temp("maze/time", time());
                if( me->query_temp("maze/warring") )
                        tell_object(me, HIR "祝你好运气！\n" NOR);
        }       
        me->set_temp("maze/name", arg);
        me->set_temp("maze/entry_room", environment(me));
        init_player(me);
        me->move(ob); 
        me->set_temp("maze/entry_room",ob);
        set_heart_beat(1);
        return 1;
}

protected void heart_beat()
{
        if( sizeof(total) )
                auto_check();
        else    set_heart_beat(0);
}

// check all the players who join the maze
protected void auto_check()
{
        object ob;
        string room;
        object *lost;
        int i;

        lost = ({ });
        for( i = 0; i < sizeof(total); i++ )
        {
                if( !objectp(total[i]) )
                {
                        total[i] = 0;
                        continue;
                }
                room = base_name(environment(total[i]));
                if( !sscanf(room, MAZE_DATA + "%*s") )
                {
        // not in maze room
                        restore_status(total[i]);
                        total[i] = 0;
                        continue;
                }
                if( total[i]->query("kee") < 1 || total[i]->query("sen") < 1 )
                        lost += ({ total[i] });
        }

   // kickout the players who lost competition
        foreach( ob in lost )
                check_out(ob);

        total -= ({ 0 });
        return;
}

// set player's override functions
protected void init_player(object me)
{
        if( !me || !living(me) || !userp(me) )
                return;
        if( !me->query_temp("maze/公共地图") )
        {       
                me->set_override("unconcious", (: call_other, __FILE__, "check_out" :));
                me->set_override("die", (: call_other, __FILE__, "check_out" :));
                me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
                me->clear_condition();
                if( sizeof(me->query_override())>0 )
                        tell_object(me,"外部函数已加载。\n");
        }
}

int check_out(object me)
{
        object ob;
        mapping my;
        string msg;
        string room;
        
        if( environment(me) && environment(me)->query("alternative_die") )
                return 0;
        room = base_name(environment(me));
        if( !sscanf(room,  MAZE_DATA +"%*s") )
        {
        // not in maze room
                total -= ({ me });
                return 0;
        }
        my = me->query_entire_dbase();
        my["eff_kee"] = me->query_maxkee();
        my["eff_sen"] = me->query_maxsen();
        my["kee"] = 1;
        my["sen"] = 1;

        tell_object(me, HIR "\n你觉得眼前一阵模糊...这下完了！\n" NOR);
        if( ob = me->query_temp("last_damage_from") )
                msg = WHT "\n$N被" + ob->name(1) + "打成重伤，狼狈而逃！\n\n" NOR;
        else    msg = WHT "\n$N身受重伤，狼狈而逃！\n\n" NOR;
        message_vision(msg, me);
        restore_status(me);
        total -= ({ me });
        me->move(me->query_temp("maze/entry_room"));
        message("vision", "一个黑影倏的窜了出来，随即就是“啪”的一声，就见" + me->name() +"摔倒了地上，一副半死不活的样子。\n", environment(me), ({ me }));
        tell_object(me, "半昏半迷中，你觉得被人拎了起来，又重重的摔倒了地上。\n");
        if( !living(me) )
                me->revive();
        return 1;
}

// overide function of quit
int check_quit(object me)
{
        if( !me )
                return 1;
        restore_status(me);
        if( arrayp(total) )
                total -= ({ me });
        me->dismiss_team(me);
        if( me->query_temp("maze/warring") )
                tell_object(me, "你逃出了副本。\n");

        // continue run quit function
        me->move(me->query_temp("maze/entry_room"));
        message("vision", "只见" + me->name() + "慌里慌张的跑了出来。\n",environment(me), ({ me }));
        return 1;
}

protected void restore_status(object me)
{
        object *t; 
        mapping cnd;
        string *ks;
        int i;

        if( me && !me->query_temp("maze/公共地图") )
        {
                me->remove_all_enemy(1);
                me->remove_all_killer();
                me->clear_condition();
                me->delete_temp("block_msg/all");
                if( me->query_temp("maze/warring") )
                        tell_object(me,HIY"\n\t\你离开了副本。\n\n"NOR);
                me->delete_temp("maze");
                if( pointerp(t=me->query_team()) )
                {
                        if( me==me->query_leader() )
                        {
                                message("team",HIW"【队伍】因为队长"+me->name()+HIW"退出了副本，本副本自动清除。"NOR"\n",t);
                                remove_maze(me,me->query_temp("maze_dir"));
                        }
                }
                else    remove_maze(me,me->query_temp("maze_dir"));
                me->delete_temp("maze_dir");
        }       
}

mixed query_maze_dir(object ob) 
{
        object env;
        string user, maze, dir,f;
        
        env = environment(ob);
        if( !env ) return 0;

        if( sscanf(base_name(env), MAZE_DATA + "%s/%s/%s/%*s",f,user, maze)!=4 )
                return 0;
        dir = query_maze_file(f+"/"+user, maze);
        return dir;
}

object query_maze_mainobj(object ob) 
{
        string file;
        file = query_maze_dir(ob) + MAZE;
        return get_object(file);
}

int remove_maze(object me, string arg)
{
        string dir,id,filename,fid;
        object ob;
        int s;
        
        if( !me || !objectp(me) || me->query_temp("maze/公共地图") ) 
                return 0;
        me->set_temp("maze/time", time());
        id = me->query("id");
        fid = sprintf("%c/%s",id[0],id);
        filename = query_maze_file(fid, arg) + MAZE;     
        ob = find_object(filename);
        if( ob ) 
                destruct(ob);
        filename = query_maze_file(fid, arg) + ENTRY;
        ob = find_object(filename);
        if( ob ) destruct(ob);
        filename = query_maze_file(fid, arg) + EXIT;
        ob = find_object(filename);
        if( ob ) destruct(ob);  
        dir =  query_maze_file(fid,arg);
        seteuid(ROOT_UID);
        ("/cmds/adm/adrm.c")->rm_dir(dir); 
        seteuid(getuid());
        return 1;
}



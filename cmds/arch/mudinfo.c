#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_DBASE;

#define SCALE   (1.0/10.0)
#define STATUS  "系统函数库改写中"

string memory_expression(int m);

int count_ppls();

void create() { seteuid(getuid(this_object())); }

int main(object me)
{
        string str;
        object *ob;
        object *o;
        float value;
        mapping r;

        r = rusage();
        value = SCALE * (r["utime"] + r["stime"]) / uptime();

        if( time()<query("last_check")+120 )
                return notify_fail("系统喘气中。\n");
                
        set("last_check",time());
        str = HIG"        .__________ 系 统 资 讯 __________.\n"NOR;
        str+= HIW"──────────────────────────\n";
        str+= " Mud 的识别名称：  " + MUD_NAME + ".\n";
        str+= " 界面系统的版本：  " + __VERSION__ + "\n";
        str+= " 系统函数库版本：  H.Y.I.I Mudlib Ver 2.0\n";
        str+= sprintf(" CPU 使用百分比：  %f %% 被这个 Mud 使用中.\n", value );
        str+= " CPU 的负担状况：  " + query_load_average() + ".\n";
        str+= sprintf(" 共使用的记忆体：  %s bytes.\n", memory_expression(memory_info()) );
        str+= " 线上使用者总数：  " + sizeof( users() ) + "  个人在线上.\n";
        str+= " 载入生物的总数：  " + sizeof( livings() ) + "  个被激活.\n";
        str+= " 注册使用者总数：  " + count_ppls() + "  个人在在本 Mud 注册.\n";
        str+= " 载入的物件总数：  " + sizeof( objects() ) + " 个物件.\n";
        str+= " 连续执行的时间：  " + CHINESE_D->chinese_period(uptime()) + "\n";

        ob = filter_array( livings(),(: $1->is_character() && !userp($1) && clonep($1) :) );
        str+= sprintf(" 共有 %d 个 NPC 物件　\n", sizeof(ob));
        
        o = filter_array( livings(),(: $1->is_character() && !userp($1) && !query_heart_beat($1) && clonep($1):) );
        str+= sprintf(" 共有 %d 个 NPC 物件无心跳　\n", sizeof(o));
        
        o = filter_array( livings(),(: $1->is_character() && userp($1) && !query_heart_beat($1) :) );
        str+= sprintf(" 共有 %d 个 玩家 无心跳　\n", sizeof(o));

        ob = objects( (: $1->is_fighting() :) );
        str+= sprintf(" 共有 %d 个人物正在战斗状态　\n", sizeof(ob));
        
        ob = objects( (: $1->is_killing() && $1->is_fighting() :) );
        str+= sprintf(" 共有 %d 个人物正在性命相搏的战斗状态　\n", sizeof(ob));
        
        reset_eval_cost();
        ob = objects( (: $1->is_killing() :) );
        str+= sprintf(" 共有 %d 个人物正和其他人物互相仇恨　\n", sizeof(ob));
        
        ob = objects( (: query_heart_beat :) );
        str+= sprintf(" 共有 %d 个物件的 heart beat 为有效状态　\n", sizeof(ob));
        
        ob = objects( (: virtualp :) );
        str+= sprintf(" 共有 %d 个虚拟物件　\n", sizeof(ob));
        
        ob = objects( (: function_exists("create_door", $1) :) );
        str+= sprintf(" 共有 %d 个房间　\n", sizeof(ob));
        
        if( !find_object(ROOM) ) ROOM->foo();
        ob = objects( (: inherits(ROOM, $1) :) );
        str+= sprintf(" 共有 %d 个物件继承标准房间　\n", sizeof(ob));
        
        reset_eval_cost();        
        if( !find_object(F_EQUIP) ) F_EQUIP->foo();
        ob = objects( (: inherits(F_EQUIP, $1) :) );
        str+= sprintf(" 共有 %d 个物件继承标准装备　\n", sizeof(ob));
        str+= HIG"──────────────────────────\n"NOR;        
        str+= " Mud 现在的状态：  " + STATUS + ".\n";
        me->start_more(str);
        return 1;
}

string memory_expression(int m)
{
        float mem;

        mem = m;
        if( mem<1024 ) return m + "";
        if( mem<1024*1024 )

                return sprintf("%.2f K", (float)mem / 1024);
        return sprintf("%.3f M", (float)mem / (1024*1024));
}

int count_ppls()
{
        int count,i;
        string *dir, *ppls;

        seteuid(getuid());

        dir = get_dir(DATA_DIR + "login/");
        for(i=0; i<sizeof(dir); i++) {
        ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/");
        count += sizeof(ppls);
        }
        return count;
}

int help() 
{
write( @HELP
指令格式：mudinfo

这个指令将会显示有关这个 Mud 的一些系统资讯。

HELP
        );
         return 1;
}


inherit ROOM;

void create()
{
  set ("short", "白虎堂");
  set ("long", @LONG

这里是武将们上朝前休息的地方，屋中并不是很大，靠墙放了
一排软椅，正中有一张八仙桌。上有茶壶茶杯和五色点心。偶
尔有几个官员出入，一个宫中侍女一旁伺候。
LONG);

        set("objects", ([
        __DIR__"npc/shinu": 1,
//      __DIR__"npc/duan" : 1,
    __DIR__"npc/xiaoyi" : 1,
        ]) );

        set("exits",
        ([ /* sizeof() == 4 */
                "east" : "/d/huanggong/guangchang",
        ]));
    set("no_clean_up", 1);
set("no_magic",1);
set("no_zhaohuan",1);
set("no_fight",1);
        setup();
}

void clear_map()
{
mixed *file,*ff;
object *inv,r;
int i,j,m,k=0,kk=0;
string str,temp;

file = get_dir("/quest/演练战/*.c", -1 );
if( !sizeof(file) )
        return 0;
for(i=0;i<sizeof(file);i++)
        {
        r = load_object("/quest/演练战/"+file[i][0]);
        if ( !r )
                {
                CHANNEL_D->do_channel(this_object(),"sys","文件载入出错；找不到/quest/演练战/"+file[i][0]);
                return 0;
                }
        inv = all_inventory(r);
        for(j=0;j<sizeof(inv);j++)
                {
                if ( !inv[j] )  continue;
                if ( !userp(inv[j]) )
                        {
                        k++;
                        inv[j]->delete_temp("last_damage_from");
                        inv[j]->die();
                        }
                else    {
                        kk++;
                        inv[j]->remove_all_killer();
                        all_inventory(r)->remove_killer(inv[j]);
                        inv[j]->team_dismiss();
                        inv[j]->delete_temp("段志玄_type");
                        inv[j]->move(this_object());
                        }
                }                
        }
set("channel_id","演练任务");
if ( k>0 )
        CHANNEL_D->do_channel(this_object(),"sys","演练地图清理完毕，共清理了"+k+"个怪物，"+kk+"位玩家离场。");
}

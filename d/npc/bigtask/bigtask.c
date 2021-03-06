#include <ansi.h>
inherit F_DBASE;
inherit F_SAVE;
#include "place.h"

string *Type = ({"找寻","救灾","杀死",});

string query_save_file() 
{
        return "/c/data/item/bigtask";
}

int quest_reward( object me, object who,object quest_item);

void create()
{
        seteuid(getuid());
        set("name","bigtask");
        set("channel_id","任务系统");
        restore();
        remove_call_out("choose_bigtask");
        call_out("choose_bigtask",5);
}

void bigtask_job(string type)
{
object newob ,m_where;
string str,m_name,shortstr,msg;
restore();
switch(type)
        {
        case "kill1" :
                newob = new(bigtask1[random(sizeof(bigtask1))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                newob->set("target",bigtask3[random(sizeof(bigtask3))]);
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                if (random(200)>197)
                        newob->carry_object(bigtask2[random(sizeof(bigtask2))]);
                CHANNEL_D->do_channel(this_object(), "job","好象"+m_name+WHT"跑到"+shortstr+WHT"去了。"NOR); 
                break;
        case "kill2" :
                newob = new(bigtask1[random(sizeof(bigtask1))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                newob->set("target",bigtask3[random(sizeof(bigtask3))]);
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","有人看到"+m_name+WHT"最近在"+shortstr+WHT"附近出没。"NOR); 
                break;
        case "kill3" :
                newob = new(bigtask1[random(sizeof(bigtask1))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                newob->set("target",bigtask3[random(sizeof(bigtask3))]);
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","据说"+m_name+WHT"到了"+shortstr+WHT"周围。"NOR); 
                break;
        case "kill4" :
                newob = new(bigtask1[random(sizeof(bigtask1))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                newob->set("target",bigtask3[random(sizeof(bigtask3))]);
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","据说最近"+m_name+WHT"逃窜至"+shortstr+WHT"附近。"NOR); 
                break;
        case "kill5" :
                newob = new(bigtask1[random(sizeof(bigtask1))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                newob->set("target",bigtask3[random(sizeof(bigtask3))]);
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","传说"+m_name+WHT"逃到了"+shortstr+WHT"。"NOR); 
                break;
        case "kill6" :
                newob = new(bigtask1[random(sizeof(bigtask1))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                newob->set("target",bigtask3[random(sizeof(bigtask3))]);
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","据说"+shortstr+WHT"出现了"+m_name+WHT"。"NOR); 
                break;
        case "kill7" :
                newob = new(bigtask1[random(sizeof(bigtask1))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                newob->set("target",bigtask3[random(sizeof(bigtask3))]);
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","有人在"+shortstr+WHT"发现"+m_name+WHT"在伤人。"NOR); 
                break;
        case "find1" :
                newob = new(bigtask4[random(sizeof(bigtask4))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","最近有人看到"+newob->query("bigtask_name")+WHT"的"+m_name+WHT"出现在"+shortstr+WHT"周围。"NOR); 
                break;
        case "find2" :
                newob = new(bigtask4[random(sizeof(bigtask4))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","据说"+newob->query("bigtask_name")+WHT"的"+m_name+WHT"在"+shortstr+WHT"附近被人发觉。"NOR); 
                break;
                
        case "find3" :
                newob = new(bigtask4[random(sizeof(bigtask4))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","有人看到"+newob->query("bigtask_name")+WHT"的"+m_name+WHT"最近在"+shortstr+WHT"附近出现。"NOR); 
                break;
        case "find4" :  
                newob = new(bigtask4[random(sizeof(bigtask4))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","有人看到"+newob->query("bigtask_name")+WHT"的"+m_name+WHT"仿佛在"+shortstr+WHT"地带发出霞光。"NOR); 
                break;
        case "find5" :  
                newob = new(bigtask4[random(sizeof(bigtask4))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job",""+newob->query("bigtask_name")+WHT"的"+m_name+WHT"在"+shortstr+WHT"一带重现。"NOR); 
                break;
        case "find6" :  
                newob = new(bigtask4[random(sizeof(bigtask4))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","据说"+newob->query("bigtask_name")+WHT"的"+m_name+WHT"流落到了"+shortstr+WHT"。"NOR); 
                break;
        case "find7" :                  
                newob = new(bigtask4[random(sizeof(bigtask4))]);
                m_name= newob->query("name");
                newob->invocation( random(sizeof(bigtask3)) );
                m_where = environment(newob);
                if (m_where) 
                        shortstr=m_where->query("short");  
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","有人在"+shortstr+WHT"一带看到"+newob->query("bigtask_name")+WHT"的"+m_name+WHT"发出的光芒。"NOR); 
                break;
        case "save1" :
                newob = new("/d/npc/bigtask/save/fire");
                newob->invocation( random(sizeof(bigtask3)) );
                m_where = environment(newob);
                if (m_where) 
                        {   
                        if (!m_where->query("shortstr"))
                                {
                                shortstr=m_where->query("short");  
                                m_where->set("shortstr",shortstr);  
                                m_where->set("tianzai","fire");  
                                m_where->set("short",shortstr+NOR"<"HIR"火灾中"NOR">");  
                                }
                        destruct(newob);
                        }
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","有人看到"+shortstr+WHT"一带着起了大火。"NOR); 
                break;
        case "save2" :
                newob = new("/d/npc/bigtask/save/fire");
                newob->invocation( random(sizeof(bigtask3)) );
                m_where = environment(newob);
                if (m_where) 
                        {   
                        if (!m_where->query("shortstr"))
                                {
                                shortstr=m_where->query("short");  
                                m_where->set("shortstr",shortstr);  
                                m_where->set("tianzai","fire");  
                                m_where->set("short",shortstr+NOR"<"HIR"着火中"NOR">");  
                                }
                        destruct(newob);
                        }
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job",""+shortstr+WHT"附近好象起火了。"NOR); 
                break;
        case "save3" :  
                newob = new("/d/npc/bigtask/save/fire");
                newob->invocation( random(sizeof(bigtask3)) );
                m_where = environment(newob);
                if (m_where) 
                        {   
                        if (!m_where->query("shortstr"))
                                {
                                shortstr=m_where->query("short");  
                                m_where->set("shortstr",shortstr);  
                                m_where->set("tianzai","fire");  
                                m_where->set("short",shortstr+NOR"<"HIR"火海中"NOR">");  
                                }
                        destruct(newob);
                        }
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","有人从"+shortstr+WHT"的火海中逃了出来。"NOR); 
                break;
        case "save4" :  
                newob = new("/d/npc/bigtask/save/water");
                newob->invocation( random(sizeof(bigtask3)) );
                m_where = environment(newob);
                if (m_where) 
                        {   
                        if (!m_where->query("shortstr"))
                                {
                                shortstr=m_where->query("short");  
                                m_where->set("shortstr",shortstr);  
                                m_where->set("tianzai","water");  
                                m_where->set("short",shortstr+NOR"<"HIB"水淹中"NOR">");  
                                }
                        destruct(newob);
                        }
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","有人看到"+shortstr+WHT"被大水淹了起来。"NOR); 
                break;
        case "save5" :          
                newob = new("/d/npc/bigtask/save/water");
                newob->invocation( random(sizeof(bigtask3)) );
                m_where = environment(newob);
                if (m_where) 
                        {
                        if (!m_where->query("shortstr"))
                                {
                                shortstr=m_where->query("short");  
                                m_where->set("shortstr",shortstr);  
                                m_where->set("tianzai","water");  
                                m_where->set("short",shortstr+NOR"<"HIB"严重积水中"NOR">");  
                                }
                        destruct(newob);
                        }
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job","连日暴雨，"+shortstr+WHT"附近被水淹没了。"NOR); 
                break;
        case "save6" :
                newob = new("/d/npc/bigtask/save/water");
                newob->invocation( random(sizeof(bigtask3)) );
                m_where = environment(newob);
                if (m_where) 
                        {   
                        if (!m_where->query("shortstr"))
                                {
                                shortstr=m_where->query("short");  
                                m_where->set("shortstr",shortstr);  
                                m_where->set("tianzai","water");  
                                m_where->set("short",shortstr+NOR"<"HIB"水灾中"NOR">");  
                                }
                        destruct(newob);
                        }
                else    shortstr="未知地点";  
                reset_eval_cost();
                CHANNEL_D->do_channel(this_object(), "job",""+shortstr+WHT"好象水灾了。"NOR);                
                break;
        }
}

string thistime_type()
{
        int i,k=4;
        string Ltype = query("last_type");
        if( !Ltype )
                return "找寻";
        if( member_array(Ltype,Type)==-1 )
                return "找寻";
        for(i=0;i<sizeof(Type);i++)
                if( Type[i]==Ltype )
                {
                        k = i;
                        break;
                }
        if( k>=2 )
                return Type[0];         
        k+= 1;
        return Type[k];
}                                       

void choose_bigtask()
{
        object *list, newob ,m_where;
        string str,m_name,shortstr,msg,tt;
        message("shout",NOR WHT"【星月任务】分配任务开始初始化。\n"NOR,users());
        tt = thistime_type();
        switch(tt) 
        {
                case "找寻" :
                        msg = sprintf(NOR HIR"%10s"NOR WHT" >>>>>> "NOR HIG"%-10s"NOR,"分配任务","找寻");
                        CHANNEL_D->do_channel(this_object(),"job",msg);
                        bigtask_job("find1");
                        bigtask_job("find2");
                        bigtask_job("find3");
                        bigtask_job("find4");
                        bigtask_job("find5");
                        bigtask_job("find6");
                        bigtask_job("find7");
                        break;
                case "救灾" :   
                        msg = sprintf(NOR HIR"%10s"NOR WHT" >>>>>> "NOR HIM"%-10s"NOR,"分配任务","救灾");
                        CHANNEL_D->do_channel(this_object(),"job",msg);
                        bigtask_job("save1");
                        bigtask_job("save2");
                        bigtask_job("save3");
                        bigtask_job("save4");
                        bigtask_job("save5");
                        bigtask_job("save6");
                        break;
                default :
                        msg = sprintf(NOR HIR"%10s"NOR WHT" >>>>>> "NOR HIR"%-10s"NOR,"分配任务","杀死");
                        CHANNEL_D->do_channel(this_object(),"job",msg);
                        bigtask_job("kill1");
                        bigtask_job("kill2");
                        bigtask_job("kill3");
                        bigtask_job("kill4");
                        bigtask_job("kill5");
                        bigtask_job("kill6");
                        bigtask_job("kill7");
                        break;
                        
        }               
        message("shout",NOR WHT"【星月任务】分配任务初始化完毕。\n"NOR,users());
        set("last_type",tt);
        save();
        remove_call_out("sys_bigtask");
        call_out("sys_bigtask",1140);
        remove_call_out("choose_bigtask");
        call_out("choose_bigtask",1200);
}

void sys_bigtask()
{
        message("shout",NOR WHT"【星月任务】分配任务将在一分钟后再次分布。\n"NOR,users());
}

int quest_reward(object me, object who,object quest_item)
{
int exp,pot,score;
object book;

if(who->query("id")!= quest_item->query("bigtask_id")) 
        return 0;
score=me->query_temp("bigtask_find")+1;        
exp =1000+20*score;
pot =150+ exp/5;

me->add("daoxing",exp,"bigtask");
me->add("combat_exp",exp,"bigtask");
me->add("potential",pot,"bigtask");
me->add("jobmark/bigtask_find",1);
CHANNEL_D->do_channel(this_object(), "job",""+me->query("name")+WHT"归还"HIG+quest_item->query("name")+NOR WHT"。"NOR); 
CHANNEL_D->do_channel(this_object(), "job","寻找:"+quest_item->query("name")+WHT"───>"+WHT"奖励:"+exp+"道行"+exp+"经验"+ pot + "潜能。"NOR); 
log_file("bigtask","["+ctime(time())+"] "+sprintf("%d. %s(%s)找到"HIW+quest_item->name()+NOR"送还"+who->name()+"获得%d的道行和%d点潜能.\n",
                                                        me->query_temp("bigtask_find"),
                                                        me->query("name"),me->query("id"),exp,pot) );
if (random(20) == 5 && (int)me->query("jobmark/bigtask_find") > 200)
        {
        book = new("/d/obj/book/tujian1");       
        book->move(me);
        CHANNEL_D->do_channel(this_object(),"rumor","听说"+me->query("name")+"得到了"HIR"《神兵图鉴》"HIM"上册！！"NOR);
        me->set("mark/tujian1", "get");
        }
if(score==15)
        {
        me->delete_temp("bigtask_find");
        me->add("combat_exp",30000);
        message("chat",HIM"【分配任务】："HIY+me->query("name")+HIM"连续完成15个寻找大任务得到"HIY+chinese_number(30000) + HIM"点武学经验的附加奖励！\n"NOR,users());
        CHANNEL_D->do_channel(this_object(), "job",""+me->query("name")+"连续完成15个寻找大任务得到"+chinese_number(30000) + "点武学经验的附加奖励！"NOR); 
        }
else me->set_temp("bigtask_find",score);
return 1;
}

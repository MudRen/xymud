#include <ansi.h>;
inherit ITEM;

string job_type(){ return "门派任务";}

nosave int t = 0;

string *dirs = ({
	//门派路径
        "/d/baihuagu","/d/jjf","/d/lingtai","/d/moon","/d/nanhai","/d/pansi","/d/sea",
	"/d/shushan","/d/xueshan","/d/qujing/wuzhuang","/d/qujing/wudidong","/d/qujing/kusong",
	//城市
	"/d/ourhome/honglou","/d/aolai","/d/changan","/d/city","/d/eastway","/d/gao",
	"/d/jz","/d/kaifeng","/d/luoyang","/d/meishan","/d/penglai","/d/westway",
	//取经路
	"/d/qujing/baotou","/d/qujing/baoxiang","/d/qujing/bibotan",
	"/d/qujing/biqiu","/d/qujing/chechi","/d/qujing/dudi","/d/qujing/fengxian","/d/qujing/firemount",
	"/d/qujing/heifeng","/d/qujing/jilei","/d/qujing/jindou","/d/qujing/jingjiling","/d/qujing/jinping",
	"/d/qujing/jisaiguo","/d/qujing/kusong","/d/qujing/lingshan","/d/qujing/maoying","/d/qujing/nuerguo",
	"/d/qujing/pansi","/d/qujing/pingding","/d/qujing/qilin","/d/qujing/qinfa","/d/qujing/qinglong",
	"/d/qujing/tianzhu","/d/qujing/tongtian","/d/qujing/wudidong",
	"/d/qujing/wuji","/d/qujing/wuzhuang","/d/qujing/xiaoxitian","/d/qujing/yinwu","/d/qujing/yuhua",
	"/d/qujing/zhujie","/d/qujing/zhuzi",
});

mapping grass_name= ([
	"百花谷"	: ({HIG"万簇团春"NOR,"wan chun",}), 
	"阴曹地府"	: ({HIB"鬼面花"NOR,"guimian hua",}),
	"将军府"	: ({HIY"将军令"NOR,"jiangjun ling",}),
	"方寸山三星洞"	: ({HIC"菩提草"NOR,"puti cao",}),
	"月宫"		: ({HIM"玉琼草"NOR,"yuqiong cao",}), 
	"南海普陀山"	: ({HIY"曼陀罗"NOR,"mantuo luo",}),
	"盘丝洞"	: ({HIG"醉生梦死"NOR,"zuisheng mengsi",}),
	"东海龙宫"	: ({HIR"龙血草"NOR,"longxie cao",}),
	"蜀山派"	: ({HIY"锯齿草"NOR,"juchi cao",}),
	"大雪山"	: ({HIW"万寒草"NOR,"wanhan cao",}),
	"五庄观"	: ({HIC"万参果"NOR,"wansheng guo",}),
	"陷空山无底洞"	: ({HIR"嗜血草"NOR,"shixie cao",}),
	"火云洞"	: ({HIR"滴火花"NOR,"dihuo hua",}),
	"其他"		: ({HIG"芒种草"NOR,"mangzhong cao",}),
]);

void create()
{
	set_name("花籽", ({ "hua zi","zi","seed"}));
  	set_weight(100);
  	if( clonep() )
    		set_default_object(__FILE__);
  	else
  	{
    		set("long","一颗小小的花籽。\n");
    		set("unit", "颗");
    		set("no_get","现在还不是时候。\n");
  	}
  	setup();
  	set_heart_beat(1+random(3));
}

void leave()
{
	if(environment())
        	message("vision","\n半空中伸出一只大手，将"+name() + "一把抓起，顿时化作虚影无影无踪。\n\n",environment());
	destruct(this_object());
}

int random_place()
{
	int i,j,k;
	object me,newob;
	mixed *file,exit;

        me=this_object();	
	i = random(sizeof(dirs));    // pick up one directory
	file = get_dir( dirs[i]+"/*.c", -1 );
	if( !sizeof(file) )
        	return 0;
	for(k=0;k<60;k++)  // try 20 times
        {
        	j = random(sizeof(file));
        	if( file[j][1]>0 ) 
                {
                	newob=load_object(dirs[i]+"/"+file[j][0]);
                	if( newob ) 
                        {  
                        	if( newob->query("no_fight") || newob->query("no_magic") 
	                          || newob->query("no_mieyao") || !(mapp(exit=newob->query("exits")))
        	                  || sizeof(exit)<1 )
                	                continue;
                        	if( me && me->move(newob,1) ) 
				{
					message("vision","\n一道霞光在天际一闪而过，从半空中掉下了一粒种子。\n\n",newob);
					set_heart_beat(1+random(3));
                	                return 1;
				}
			}
                }
        }
	return 0;
}

string invocation(object who)
{
	object me = this_object();
	if( !who )  
		return 0;
	if( !random_place() )
	{
		leave();
		return 0;
	}
	set("owner_id",who->query("id"));
	set("owner",who);
	set("family_name",who->query("family/family_name"));
	who->set_temp("family_zi",this_object());
	return MISC_D->find_place(environment());
}

string query_names()
{
	string fam,str;
	if( !stringp(fam=query("family_name"))
	 || undefinedp(grass_name[fam]) )
		fam = "其他";
	str = grass_name[fam][0]+"("+capitalize(grass_name[fam][1])+")";
	return COLOR_D->clean_color(str);
}

void init()
{
	add_action("do_get","get");
}

void grow()
{
	object me = this_object();
  	string name = me->query("name");
  	string fam;

	if( !environment() )
		return;
	if( query("create") )
		return;
	t = t+1;
	if( query("id") == "hua zi")
  	{
    		if( random(6)==0 || t==4 )
    		{
      			message("vision","花籽绽裂开，露出了一颗绿芽。\n",environment());
      			set_name("绿芽", ({ "lv ya","ya"}));
			set("long","一株正在长大的小绿芽。\n");
      			set("unit", "株");
      			me->set("stay_time",time());
    		}
    		else
    		{
    			message("vision","花籽动了一下，胀大了一点点。\n",environment());
    			t = t+1;
    		}
  	}
	else if(query("id") == "lv ya" )
  	{
    		if( random(9) == 0 || t== 6)
    		{
      			message("vision","绿芽终于长高了，在风中欢快地摇弋。\n",environment());
      			me->set_name("小草", ({ "xiao cao","cao"}));
      			me->set("long","一棵茁壮的小草，上面有花苞。\n");
      			me->set("unit", "棵");
      			me->set("stay_time",time());
    		}
    		else	
    		{
    			message("vision","绿芽咔嚓一声长高了一截。\n",environment());
    			t = t+1;
    		}
  	}
	else if( me->query("id") == "xiao cao")
  	{
    		if( random(12) == 0 || t>=9 )
    		{
    			if( !stringp(fam=query("family_name"))
    			 || undefinedp(grass_name[fam]) )
				fam = "其他";
			me->set_name(grass_name[fam][0],({grass_name[fam][1],"family xiancao",}));
			me->set("stay_time",time());							    	
			me->set("create",1);		 
      			message("vision","微风吹过，"+name()+"上传来阵阵异香，看来是成熟了。\n\n",environment());
      			return;
    		}
    		else
    		{
    			message("vision",({"小草在风中跳起了舞。\n","小草微笑着。\n",})[random(2)],environment());
    			t = t+1;
    		}
  	}
  	set_heart_beat(1+random(3));
}

void heart_beat()
{
	if( !environment() )
		return;
	grow();
	if( time()>query("stay_time")+600 )
	{
		set_heart_beat(0);
		leave();
		return;
	}
}

int do_get(string arg)
{
	int lvl,exp_r, pot_r,dx_r;
	object me = this_player();
	if( !arg || !id(arg) )
		return 0;
	if( environment()->is_character() )
		return 0;	
	if( !query("owner_id") || !query("owner") )
		return 0;
	if( query("owner_id")==me->query("id")
	 && me==query("owner") && query("create") )
	{
		if( random(4) )	
			tell_object(me,HIY"【师门】你成功为师门守护了"+query("name")+HIY"。\n"NOR);
		else	CHANNEL_D->do_channel(this_object(),"rumor","听说"+me->name()+HIM"成功为师门守护了"+query("name")+HIM"。"NOR);	
		exp_r = 10000;
        	pot_r = exp_r*18/30+1;
		dx_r = exp_r*3/5+random(exp_r/5);
	
               	QUEST_D->job_reward_player(me,"combat_exp",exp_r,job_type());
		QUEST_D->job_reward_player(me,"daoxing",pot_r,job_type());
		QUEST_D->job_reward_player(me,"potential",dx_r,job_type());
		tell_object(me,HIY+me->finish_job(job_type(),({exp_r,dx_r,pot_r}))+NOR);
		lvl = me->query_job_level("门派任务");
		lvl+= 1;
		lvl*= 15;
		me->add("faith",lvl);
		tell_object(me,HIY"【师门】你得到了"+lvl+"点门派贡献。\n"NOR);
		lvl = me->query_job_level("门派任务");
		tell_object(me,HIY"【噩梦】本轮已经完成 "HIR+lvl+"/10"HIY"个，已完成"HIR+me->query_temp("mark/evil_family")+HIY"轮。\n"NOR);                    		
		if( lvl==10 )
                {
                	tell_object(me,HIY"恭喜！你完成了一轮噩梦级别的门派任务。\n"NOR);
                    	me->add_temp("mark/evil_family",1);
                    	me->add("faith",100);
                    	tell_object(me,HIY"你得到了100点门派贡献的追加奖励。\n"NOR);
		}
		me->delete_temp("family_zi");
        	destruct(this_object());
		return 1;
	}	 	
	else	return 0;
}

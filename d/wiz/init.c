// Room: /d/wiz/init.c
// mon 3/18/99
#include <ansi.h>
inherit ROOM;

int get_start1(object me);
void show_gift(object me);
string _show_gift(object me);
void do_finish(object me);
void get_start(object me);
int confirm(string yn, object me);
string start_room="/d/aolai/cuixiang";
string *index=({
	"str","con","int","spi","cps","per","cor","kar",
});

mapping giftn=([
	"str":"体格", "con":"根骨", "int":"悟性", "spi":"灵性",
	"cps":"定力", "per":"容貌", "kar":"福缘", "cor":"胆识",
]);

mapping gift=([
	"str":20, "con":20, "int":25, "spi":25,
	"cps":20, "per":20, "kar":20, "cor":20,
]);

void create()
{
	set("short", "\n欢迎光临西游类修真泥潭---小雨西游！");
	set("no_fight",1);
	set("no_magic",1);
	setup();
}

void enter_world(object who)
{
	object env;
	string zz,start_room;
	if( !who || !userp(who) )
		return;
	start_room = "/d/aolai/cuixiang";
	
	who->init_money();
    	who->init_balance();
    	who->set("combat_exp",0);
    	who->set("daoxing",0);
        who->set("startroom",start_room);
        who->delete_temp("gifts");	

    	tell_object(who,"\n\n\n好！祝你西天取经早成正果！\n\n\n");
    	tell_object(who,
	"只见眼前霞光一闪，你已经来到了一个陌生的世界（ｌｏｏｋ）．．．\n\n");
	
    	if( ( "/adm/daemons/band"->create_char_banned(query_ip_number(who)) == 1
    	   || "/adm/daemons/band"->is_banned(query_ip_number(who)) == 1 ) 
	   && !wizardp(who)) 
	{
		who->move("/d/wiz/guest");
	    	log_file( "allcont", sprintf("%s from banned site\n",who->query("id")) );
	    	return;
    	}
    	env=load_object(start_room);
    	message("shout",({"\n朵朵祥云忽然涌现在天际。\n\n",
		"\n天边一颗流星倏地划过．．．\n\n",
		"忽听远处惊天动地一声巨响，随即一道金光闪过．．．\n"})
	    [random(3)],users());
    	who->move(env,1);
    	tell_object(who,"\n"HIY"【系统】"HIR"20"HIY"级之前，你可以在长安南城客栈的"HIC"新手准备室"HIY"找"HIG"小雨"HIY"要一次启动资金。"NOR"\n");
	who->save();        		
	return;
}	
	

void init_gift(object who)
{
	int ok;
    	mapping gt;	
	if( !who )
		return;
	gt = who->query_temp("gifts");
    	if( !gt || !mapp(gt) ) 
    	{
		write("Something wrong.\n");
		return;
    	}
    	if((int)(gt["str"]+gt["con"]+gt["int"]+gt["spi"])>90) 
    	{
		write("你的"+giftn["str"]+"、"+giftn["con"]+"、"+giftn["int"]+"及"+giftn["spi"]+"之和不能多于 90 。\n");
		get_start(who);
		return;
    	}
    	ok=0;
    	while(!ok) 
    	{
		gt["cps"]=10+random(21);
		if(who->query("gender")=="男性")
	  		gt["per"]=10+random(21);
		else	gt["per"]=15+random(16);  
		gt["kar"]=10+random(21);
		gt["cor"]=80-gt["cps"]-gt["per"]-gt["kar"];
		if(gt["cor"]>=10 && gt["cor"]<=30) 
			ok=1;
    	}
}

void init()
{
	object me=this_player();
    
    	if(!userp(me)) return;
    	if(!wizardp(me) && (int)me->query("no_gift")==0 ) 
	{	
		me->move(start_room);
		return;
    	}  
            me->set("combat_exp",1);
            me->set("daoxing",1);
	add_action("do_block","",1);
    	add_action("get_start1","start");
//    	add_action("do_restart","restart");
    	if(me->query("no_gift")) 
    	{
      		me->set_temp("gifts",copy(gift));
      		me->set_temp("gift_left",0);
      		get_start1(me);
    	}
}

int get_start1(object me)
{
    	if( !me )
    		return 1;
    	write("\n\n欢迎光临西游类修真泥潭---小雨西游！\n");
    	write(@LONG
在开始你的西游历程之前，首先要为自己所创造的人物选择一个合适
的天赋，因为这将对你今后的发展有重大的影响。
下面是人物各天赋属性的具体作用
	□ 体格 1点体格增加4点物理攻击，1点物理防御，2点气血
	□ 悟性 1点悟性增加2点精力，有时还会影响到领悟的成功率
	□ 灵性 1点灵性增加4点法术攻击，1点法术防御，2点法力
	□ 根骨 1点根骨增加50点气血，20点法力
	□ 胆识 1点胆识增加3点精力，另外还影响到出招快慢
	□ 定力 1点定力增加2点法术防御，2点物理防御
	□ 容貌 影响到部分解密的触发率 以及诱惑类招式的成功率
	□ 福缘 打宝的掉落率，以及部分解密的触发或成功率
注意的是在选择天赋时，定力/容貌/胆识/福缘 是每次随机的，所以如果
你对当前的天赋不满意，可以直接按 回车 来重新随机，而不需要进入游
戏后自身以重新建立人物。

LONG
	);
    	get_start(me);
    	return 1;
}

void get_start(object me)
{
    	if(!me) return;
	init_gift(me);    	
    	show_gift(me);
    	input_to("get_input",me);
}

void get_input(string arg, object me)
{
    	int ind;

    	if(!me) return;
        if( arg &&  arg=="quit" )
    	{
		//write(CYN"\n你确定要放弃该帐号而退出吗？(y/n)\n"NOR);
		//input_to((: confirm :), me);
    		return;
    	}
    	if( !arg || sscanf(arg,"%d",ind)!=1 || ind<0
	 || (ind>3 && ind!=9)) 
	{
		get_start(me);
		return;
    	}
    	if(ind<8) 
    	{
		write("请输入"+giftn[index[ind]]+"的新取值[10-30]：");
		input_to("get_number",me,ind);
		return;
    	} 
    	else {
		write("你确定接受当前的天赋设置吗？[y/n]");
		input_to("get_finish",me);
		return;
    	}
}

void get_finish(string arg, object me)
{
    	if(!me) return;
    	if(!arg) {
		write("你确定接受当前的天赋设置吗？[y/n]");
		input_to("get_finish",me);
		return;
    	}
    	if(arg[0..0]=="y" || arg[0..0]=="Y") {
		do_finish(me);
		return;
    	}
    	if(arg[0..0]=="n" || arg[0..0]=="N") {
		get_start(me);
		return;
    	}
    	write("你确定接受当前的天赋设置吗？[y/n]");
    	input_to("get_finish",me);
    	return;
}

void show_gift(object me)
{
    	write(_show_gift(me));
}

string _show_gift(object me)
{
    	mapping my;
    	string result;
    	int left;

    	if(!me) return "";
    	my=me->query_temp("gifts");
    	left=me->query_temp("gift_left");
    	if(!my) return "";
    
    	result=("\n");
    	result+="─────────────────────────\n";
	result+=sprintf(
	    " 0. 体格：[%d]        1. 根骨：[%d]\n"+
	    " 2. 悟性：[%d]        3. 灵性：[%d]\n"+
	    " 4. 定力：[%d]        5. 容貌：[%d]\n"+	    
            " 6. 胆识：[%d]        7. 福缘：[%d]\n",
	    my["str"],my["con"],my["int"],my["spi"],
	    my["cps"],my["per"],my["cor"],my["kar"],	    
	    );
    	result+="─────────────────────────\n";
	if(left)
      		result+="你现有"+chinese_number(left)+"点天赋还没有分配。\n";
	result+= "如果你对天赋不满意，可以输入 0-3 来重新获得随机数。\n";      		
    	result+="请选择你想重新设置哪一项天赋的取值[0-3]，\n选择[9]则接受当前的设置：";
    	return result;
}

void do_finish(object me)
{
    	mapping gt;
    	int i, left, ok;
    	string *key;
    	object env;
    
    	if(!me) return;
    	left=me->query_temp("gift_left");
    	if(left>0) 
    	{
		write("你总共可有 90 点天赋，现在还有剩余"+chinese_number(left)+"点天赋没有分配。\n");
		write("你是否想继续分配这些剩余点数？[y/n]");
		input_to("continue_finish",me);    
		get_start(me);
		return;
    	} else if(left<0) 
    	{
        	write("Sth wrong, let wiz know.\n");
        	return;
    	}   
	gt=me->query_temp("gifts");
    	if(!gt || !mapp(gt)) 
    	{
		write("Something wrong.\n");
		return;
    	}
    	if((int)(gt["str"]+gt["con"]+gt["int"]+gt["spi"])>90) 
    	{
		write("你的"+giftn["str"]+"、"+giftn["con"]+"、"+giftn["int"]+"及"+giftn["spi"]+"之和不能多于 90 。\n");
		get_start(me);
		return;
    	}

    /*
    if((int)(gt["cps"]+gt["per"]+gt["kar"]+gt["cor"])>80) {
	write("你的"+giftn["cps"]+"、"+
		giftn["per"]+"、"+
		giftn["kar"]+"及"+
		giftn["cor"]+"之和不能多于 80 。\n");
	get_start(me);
	return;
    }
    */
key=keys(giftn);
    i=sizeof(key);
    while(i--) {
	if(undefinedp(gt[key[i]])) {
	    write("Sth wrong, tell wizard.\n");
	    return;
	}
	me->set(key[i],gt[key[i]]);
    }
    me->delete("no_gift");
    me->flush_buffer();
    enter_world(me);

    return;
}
    
void continue_finish(string arg, object me)
{
    if(!me) return;
    if(!arg) {
	write("你是否想继续分配这些剩余点数？[y/n]");
	input_to("continue_finish",me);    
	return;
    }
    if(arg[0..0]=="y" || arg[0..0]=="Y") {
	get_start(me);
	return;
    }
    if(arg[0..0]=="n" || arg[0..0]=="N") {
	me->set_temp("gift_left",0);
	do_finish(me);
	return;
    }
	write("你是否想继续分配这些剩余点数？[y/n]");
	input_to("continue_finish",me);    
    return;
}
void get_number(string arg, object me, int ind)
{
    mapping gt;
    int value, old_value;
    string name;
    
    if(!me) return;
    if(!arg || sscanf(arg,"%d",value)!=1) {
	write("请输入"+giftn[index[ind]]+"的新取值[10-30]：");
	input_to("get_number",me,ind);
	return;
    }
    if(value<10 || value>30) {
	write("数值应介于 10 和 30 之间。\n");
	write("请输入"+giftn[index[ind]]+"的新取值[10-30]：");
	input_to("get_number",me,ind);
	return;
    }
   
    gt=me->query_temp("gifts");
    if(!gt || !mapp(gt)) {
	write("Something wrong.\n");
	return;
    }
    
    name=index[ind];
    old_value=gt[name];
    gt[name]=value;
    
    if((int)(gt["str"]+gt["con"]+gt["int"]+gt["spi"])>90) {
	gt[name]=old_value;
	write("你的"+giftn["str"]+"、"+
		giftn["con"]+"、"+
		giftn["int"]+"及"+
		giftn["spi"]+"之和不能多于 90 。\n");
	write("请输入"+giftn[index[ind]]+"的新取值[10-30]：");
	input_to("get_number",me,ind);
	return;
    }
/*
    if((int)(gt["cps"]+gt["per"]+gt["kar"]+gt["cor"])>80) {
	gt[name]=old_value;
	write("你的"+giftn["cps"]+"、"+
		giftn["per"]+"、"+
		giftn["kar"]+"及"+
		giftn["cor"]+"之和不能多于 80 。\n");
	write("请输入"+giftn[index[ind]]+"的新取值[10-30]：");
	input_to("get_number",me,ind);
	return;
    }
 */   
    me->add_temp("gift_left",old_value-value);
    me->set_temp("gifts",gt);
    write("你将"+giftn[name]+"设为"+chinese_number(value)+"。\n");

    get_start(me);
}


int do_block(string arg)
{
    	object me=this_player();
    	string verb=query_verb();

    	if(!userp(me) || wizardp(me)) 
    		return 0;
    	if( verb=="look" 
    	 || verb=="help" 
    	 || verb=="story" 
    	 || verb=="say" 
    	 || verb=="restart" ) 
    	 	return 0;
	if( verb=="quit" )
		return 0;	     	 	
       return 1;
}

int confirm(string yn, object me)
{
	if(yn[0]=='y' || yn[0]=='Y' )
	{
        me->command("quit");
		return 1;
	}
 	else 
 	{
	    	write("你确定接受当前的天赋设置吗？[y/n]");
    		input_to("get_finish",me);
		return 1;
	}
}

int do_restart(string arg)
{
	object me = this_player();
	if( wizardp(me) || !userp(me) )
		return 1;
	write(CYN"\n你确定要放弃该帐号而退出吗？(y/n)\n"NOR);
	input_to((: confirm :), me);
        return 1;
}
	

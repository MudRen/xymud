// Modified by vikee
// 2001-2-15 13:12
// Natured.c
//add by lestat 2001-2

#include <ansi.h>

#define TIME_TICK ((time()-1000000000)*60)
#define TIME_TICK1 ((time()-1150000000)*60)
/*
#define TIME_TICK ((time()-1150000000)*60)
#define TIME_TICK1 ((time()-1150000000)*60)
*/

#define PUBU      "d/pansi/pubu"
#define ZIYUN      "d/pansi/shishi5"
#define CENTER      "d/city/center"

int current_day_phase, current_month;
mapping *day_phase;
int online_user();
int night;
int night_test;
string ppl;
nosave string Jijie;

string *month_time = ({
	"春天悄悄地走来了，","春风轻轻地拂过你的脸庞，","天气逐渐变暖了，","已经是初夏时节了，",
	"知了的叫声让你感觉到了盛夏的气息，","天气变得非常闷热，","虽然是秋天了，天气还是有些热，",
	"中秋佳节快到了，","一阵秋风吹来，卷起了地上的落叶，","秋去冬来，","寒风凛冽，","快到年关了，",
});

string *month_desc = ({
	HIW"「隆冬」:"NOR,HIW"「寒冬」:"NOR,HIG"「初春」:"NOR,HIG"「早春」:"NOR,HIG"「阳春」:"NOR,HIC"「初夏」:"NOR,
	HIC"「盛夏」:"NOR,HIR"「仲夏」:"NOR,HIY"「初秋」:"NOR,HIY"「高秋」:"NOR,YEL"「深秋」:"NOR,WHT"「初冬」:"NOR,
});

int query_current_day_phase() { return current_day_phase; }

mapping *read_table(string file);

void init_day_phase();

void create()
{
	string get_month, get_day;
	mixed *local;
	local = localtime(TIME_TICK1);
        get_day = CHINESE_D->chinese_number(local[3]);
	get_month = CHINESE_D->chinese_number(local[4]);
	switch(get_month)
	{
		//spring weather
		case "三":
		case "四":
		case "五":
     			switch(random(3))
     			{
				case 0: day_phase = read_table("/adm/etc/nature/spring_rain");break;
				case 1: day_phase = read_table("/adm/etc/nature/spring_sun");break;
				case 2: day_phase = read_table("/adm/etc/nature/spring_wind");break;
     			}
     			Jijie = "春";
     			break;
		//summer weather
		case "六":
		case "七":
		case "八":
     			switch(random(3))
     			{
				case 0: day_phase = read_table("/adm/etc/nature/summer_rain");break;
				case 1: day_phase = read_table("/adm/etc/nature/summer_sun");break;
				case 2: day_phase = read_table("/adm/etc/nature/summer_wind");break;
     			}
     			Jijie = "夏";
     			break;
		case "九": //秋
		case "十":
		case "十一":
     			switch(random(3))
     			{
				case 0: day_phase = read_table("/adm/etc/nature/autumn_rain");break;
				case 1: day_phase = read_table("/adm/etc/nature/autumn_sun");break;
				case 2: day_phase = read_table("/adm/etc/nature/autumn_wind");break;
     			}
     			Jijie = "秋";
     			break;
                case "零": //冬
		case "二":
     			switch(random(3))
     			{
				case 0: day_phase = read_table("/adm/etc/nature/winter_rain");break;
   				case 1: day_phase = read_table("/adm/etc/nature/winter_sun");break;
				case 2: day_phase = read_table("/adm/etc/nature/winter_wind");break;
     			}
     			Jijie = "冬";
     			break;
		case "一":
        		if(get_day=="一")
        		{
      				day_phase = read_table("/adm/etc/nature/spring");
      				Jijie = "春";
      			}
      			else
      			{
      				switch(random(3))
     				{
					case 0:	day_phase = read_table("/adm/etc/nature/winter_rain");break;
					case 1: day_phase = read_table("/adm/etc/nature/winter_sun");break;
					default: day_phase = read_table("/adm/etc/nature/winter_wind");break;
     				}
     				Jijie = "冬";
     			}
             		break;
		default:
			day_phase = read_table("/adm/etc/nature/day_phase");
			Jijie = "NONE";
			break;
	}
	init_day_phase();
}
mixed *getTime(int date) {
	int curYear, curMonth, curDay, curSheChen, curKe, curDayTime;

	curDayTime = date % 1440;
	curKe = (date % 120) / 30;
	curSheChen = (date / 120) % 12;
	curDay = (date / 1440) % 30;
	curMonth = (date / 43200) % 12;
	curYear = (date / 518400);

	return ({curKe, curSheChen, curDay, curMonth, curYear, curDayTime});
}
void update_jijie()
{
	string get_month, get_day;
	mixed *local;
	local = localtime(TIME_TICK1);
        get_day = CHINESE_D->chinese_number(local[3]);
	get_month = CHINESE_D->chinese_number(local[4]);
	switch(get_month)
	{
		case "三":
		case "四":
		case "五": Jijie = "春";break;
		case "六":
		case "七":
		case "八": Jijie = "夏";break;
		case "九":
		case "十":
		case "十一":Jijie = "秋";break;
                case "零":
		case "二": Jijie = "冬"; break;
		case "一":
        		if(get_day=="一")
      				Jijie = "春";
      			else 	Jijie = "冬";
             		break;
		default: Jijie = "NONE";break;
	}
}

string query_jijie()
{
	update_jijie();
	return Jijie;
}

void init_day_phase()
{
	mixed *local;
	int i, t;

	local = localtime(TIME_TICK1);
	t = local[2] * 60 + local[1];           // hour * 60 + minutes

	for( i=0; i < sizeof(day_phase); i++)
	{
		if( t >= day_phase[i]["length"] )
			t -= (int)day_phase[i]["length"];
		else	break;
	}
	current_day_phase = (i==0? sizeof(day_phase)-1: i - 1);
	current_month = local[4];

	// MUD 运行时间久了，时间会有偏差，这里是调整程序，每小时执行一次
	remove_call_out("init_day_phase");
	call_out("init_day_phase", 3600);

	remove_call_out("update_day_phase");
	call_out("update_day_phase",(int)day_phase[(current_day_phase+1) % sizeof(day_phase)]["length"] - t);
}

void update_day_phase()
{
	int i,j;
	object *inusers,envroom;
	string str;
	remove_call_out("update_day_phase");
	current_day_phase = (++current_day_phase) % sizeof(day_phase);
	if( !undefinedp(day_phase[current_day_phase]["event_fun"]) )
		call_other(this_object(), day_phase[current_day_phase]["event_fun"]);
        i=0;
	// here is modified by vikee 2001-2-15 13:15
        str=HIG"╠╣"+NOR+CYN"窗外"+NOR+HIG"╠╣"NOR+day_phase[current_day_phase]["time_msg"];
        inusers=users();
  	reset_eval_cost();
        for (i;i<(j=sizeof(inusers));i++)
        {
        	envroom=environment(inusers[i]);
            	if (envroom)
           	{
            		if ( intp(envroom->query("outdoors")))
             		{
               			if (envroom->query("outdoors")<1)
             				tell_object(inusers[i],str+"\n");
               			else 	tell_object(inusers[i],day_phase[current_day_phase]["time_msg"]+"\n");
             		}
            		else	tell_object(inusers[i],day_phase[current_day_phase]["time_msg"]+"\n");
          	}
       }
       call_out("update_day_phase", day_phase[current_day_phase]["length"]);
}

void event_midnight()
{
	update_jijie();
	switch(Jijie)
	{
		case "春" :
     			switch(random(3))
     			{
				case 0: day_phase = read_table("/adm/etc/nature/spring_rain");break;
				case 1:	day_phase = read_table("/adm/etc/nature/spring_sun");break;
				default: day_phase = read_table("/adm/etc/nature/spring_wind");break;
     			}
     			break;
		case "夏" :
     			switch(random(3))
     			{
				case 0: day_phase = read_table("/adm/etc/nature/summer_rain");break;
				case 1: day_phase = read_table("/adm/etc/nature/summer_sun");break;
				default: day_phase = read_table("/adm/etc/nature/summer_wind");break;
     			}
	      		break;
		case "秋" :
     			switch(random(3))
     			{
				case 0: day_phase = read_table("/adm/etc/nature/autumn_rain");break;
				case 1: day_phase = read_table("/adm/etc/nature/autumn_sun");break;
				default: day_phase = read_table("/adm/etc/nature/autumn_wind");break;
     			}
     			break;
		case "冬" :
     			switch(random(3))
     			{
	 			case 0: day_phase = read_table("/adm/etc/nature/winter_rain");break;
				case 1: day_phase = read_table("/adm/etc/nature/winter_sun");break;
				case 2: day_phase = read_table("/adm/etc/nature/winter_wind");break;
     			}
     			break;
		default : day_phase = read_table("/adm/etc/nature/day_phase");break;
	}
}

// This is called everyday noon by update_day_phase, defined in the
// "event_fun" field in /adm/etc/nature/day_phase
int online_user()
{
	int i,ppl_cnt;
	object *usr = users();
	for(i=0; i<sizeof(usr); i++)
	{
		if( !environment(usr[i]) )
			continue;
		ppl_cnt++;
	}
	return ppl_cnt;
}

void event_sunrise()
{
	int avg_num,record_num,online_num,total_num,times;
        string avg_temp,total_temp,times_temp;
        object *user=users();

        online_num = online_user();
        times = atoi(read_file(__DIR__"record_times",1));
        times++;
        record_num = atoi(read_file(__DIR__"total_num",1));
        total_num = online_num + record_num;
        avg_num = total_num / times;
        total_temp = sprintf("%d",total_num);
        times_temp = sprintf("%d",times);
        avg_temp = sprintf("%d",avg_num);
        write_file(__DIR__"total_num",total_temp,1);
        write_file(__DIR__"record_times",times_temp,1);
        write_file(__DIR__"avguser",avg_temp,1);
}

void event_evening(){ return;}

//这部分还是通过NPC来设置吧
void event_night(){night=1;}

void event_dawn(){night=0;}

void event_noon(){return;}

string outdoor_room_description()
{
	return "    " + sprintf(day_phase[current_day_phase]["desc_msg"],month_desc[current_month]) + "。\n";
}

int set_night(int arg)
{
	night=arg;
	return 1;
}

int night(){ return night;}

string game_time()
{
	return CHINESE_D->chinese_date(TIME_TICK1);
}

mapping *read_table(string file)
{
	string *line, *field, *format;
	mapping *data;
	int i, rn, fn;

	line = explode(read_file(file), "\n");
	data = ({});
	for(i=0; i<sizeof(line); i++)
	{
		if( line[i]=="" || line[i][0]=='#' )
			continue;
		if( !pointerp(field) )
		{
			field = explode( line[i], ":" );
			continue;
		}
		if( !pointerp(format) )
		{
			format = explode( line[i], ":" );
			continue;
		}
		break;
	}
	for( rn = 0, fn = 0; i<sizeof(line); i++)
	{
		if( line[i]=="" || line[i][0]=='#' )
			continue;
		if( !fn )
			data += ({ allocate_mapping(sizeof(field)) });
		sscanf( line[i], format[fn], data[rn][field[fn]] );
		fn = (++fn) % sizeof(field);
		if( !fn ) ++rn;
	}
	return data;
}

mapping *query_day_phase() { return day_phase; }

string query_time_wuxing()
{
	string shi,*sym_dee = ({ "子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥" });
	int t = ((time()-1150000000)*60);
	mixed *local = localtime(t);
	shi = sym_dee[(local[2]%24)/2];
	switch(shi)
	{
		case "子" : return "水";
		case "丑" : return "土";
		case "寅" : return "木";
		case "卯" : return "木";
		case "辰" : return "土";
		case "巳" : return "火";
		case "午" : return "火";
		case "未" : return "土";
		case "申" : return "金";
		case "酉" : return "金";
		case "戌" : return "土";
		case "亥" : return "水";
		default   : return 0;
	}
}

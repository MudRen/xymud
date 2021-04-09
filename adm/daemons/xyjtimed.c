//[1;31m该文件关联系统过多，禁止随意更改任何参数[0m
// Created by waiwai@2001/07/06
// Last Modified By waiwai@2002/12/05
// Update by waiwai@2003/04/10 修改用于西游记

// Last Modified By jingxue 12.25.2004 for xycq3
// 增加现实节日判断

//// #pragma optimize
//// #pragma save_binary

#include <ansi.h>
#include <command.h>

#include <localtime.h>

// 定义元年一月一日一时一刻的时间
// 定义为999900000是这个时间是西游记建立日期
// 是按照实际现实日期计算所得
//#define WKZ_TIME 1057442400
//#define WKZ_TIME 999900000
#define ONE_YEAR_TIME 172800  // 每年所需要的时间,这里为48小时

/**************************************************************************************************/
#define GALA_C "无节日"
// 农历节日
// 遇到节日需要巫师自行修改此参数
// 无农历节日修改为 无 或者 无节日
// 有农历节日修改为 节日名称 例如 春节
/**************************************************************************************************/

/**************************************************************************************************/
#define DOUBLE_REWARD 100
// 经验基数
// added by jingxue 12.25.2004
// 计算让节日是否给予双倍或者多倍奖励
// 系统遇到节日将给予双倍奖励
// 巫师需要提高奖励只需要修改经验基数DOUBLE_REWARD
// 节日经验系数一般为200，也就是经验双倍200%
// 经验基数DOUBLE_REWARD为100则为正常值，也就是经验将为100%
// type为奖励类型
// type为1则只按普通比例奖励，不考虑节日系数和经验基数
// type为2则只考虑节日系数，不考虑经验基数
// type为3则不考虑节日系数，只考虑经验基数
// type为4则既考虑节日系数，又考虑经验基数
/**************************************************************************************************/


inherit F_CLEAN_UP;
mapping check_time(int time_now);
string xyjtime();
string day_event(){ return NATURE_D->outdoor_room_event(); }

string check_season();			// 纪年季节
string check_month_desc();			// 月份前缀
string check_sxt(object ob);		// 生肖图谱
string check_xzt(object ob);		// 星座图谱
string check_weather_season();		// 时辰季节
string check_daoxing(int gain);		// 道行调用
string check_usr_birthday(object ob);	// 个人生日
/**************************************************************************************************/

string query_gala(int type);		// 返回节日
int query_double_reward(int type);	// 经验系数
/**************************************************************************************************/

mapping check_time(int time)
{
	int t;
    	mapping date;
	mixed *local;

    	t = (time-TIME_TICK)*60;
	local = localtime(t);
       	date =([
          	"YEAR"     : chinese_number((time-TIME_TICK)/1388476115) + "年", //从2013.12.31日开始
          	"MONTH"    : ((local[LT_MON]+1)==1?"元":chinese_number(local[LT_MON]+1)) +"月",
          	"DAY"      : chinese_number(local[LT_MDAY] + (local[LT_HOUR]>23? 1 : 0)) +"日",
          	"HOUR"     : chinese_number(local[LT_HOUR]) + "时",
          	"QUARTER"  : chinese_number(local[LT_HOUR]%2 * 2 + local[LT_MIN]/30 + 1)+"刻",
          	"MIN"      : chinese_number(local[LT_MIN]) +"分",
          	"WDAY"     : "星期"+ ((local[LT_WDAY]==0)?"日":chinese_number(local[LT_WDAY])),
          	"SYEAR"    : chinese_number(((time-TIME_TICK)/525600)/1000)
          			+chinese_number((((time-TIME_TICK)/525600)%1000)/100)
          			+chinese_number((((time-TIME_TICK)/525600)%100)/10)
          			+chinese_number(((time-TIME_TICK)/525600)%10)
          			+ "年",
        ]);
        return date;
}

string xyjdate()
{
	string day;
       	mapping date;

       	date = check_time(time());
       	day = date["YEAR"]+"  "+date["MONTH"]+date["DAY"]+date["HOUR"]+date["MIN"]+"  "+date["WDAY"];

       	return day;
}

string xyjtime()
{
	string day;
       	mapping date;

       	date = check_time(time());
       	day = date["YEAR"]+date["MONTH"]+date["DAY"];

       	return day;
}
// 西游记纪年时间的生日
string check_usr_birthday(object ob)
{
	mapping date = check_time(ob->query("birthday"));
       		return date["SYEAR"]+date["MONTH"]+date["DAY"]+date["HOUR"]+date["MIN"];
}

/**************************************************************************************************/

// 纪年的调用暂时还可以用模糊的月份方式吧
string check_season()
{
	string month;
	string season;
	string time;
	int hour;

	mapping date=check_time(time());
	month=date["MONTH"];
	hour=date["HOURR"];

	if(hour <6 && hour>0)                time="凌晨";
	     else if(hour<8 && hour >=6)     time="早上";
	     else if(hour<12 && hour>=8)     time="上午";
	     else if(hour==12)               time="中午";
	     else if(hour<19 && hour>12)     time="下午";
	     else if(hour<24 && hour>=19)    time="晚上";
	     else if (hour==24 || hour==0)   time="子夜";

	switch (month) {
	       case "十二月":
               season = "初冬的"+time; break;
	       case "元月":
	         season = "隆冬的"+time; break;
	       case "二月":
               season = "冬末的"+time; break;
	       case "三月":
               season = "初春的"+time; break;
	       case "四月":
               season = "春季的"+time; break;
	       case "五月":
               season = "春末的"+time; break;
	       case "六月":
               season = "初夏的"+time; break;
	       case "七月":
               season = "盛夏的"+time; break;
	       case "八月":
               season = "夏末的"+time; break;
	       case "九月":
               season = "初秋的"+time; break;
	       case "十月":
               season = "秋季的"+time; break;
	       case "十一月":
               season = "深秋的"+time; break;
       }
       return season;
}
/**************************************************************************************************/

// Added By waiwai@2002/12/05
// 增加游戏时辰的季节显示，与纪年时节是不同的
// 只有这种调用方式才是最准确的
string check_weather_season()
{
	string get_season;
	string season;
	get_season= NATURE_D->check_seasonF();

      if( day_event() == "event_dawn" ) {
       switch (get_season) {
	       case "SpringA-Sun":
	       case "SpringA-Rain":
	       case "SpringA-Wind":
	       season = "初春的凌晨"; break;
	       case "SpringB-Sun":
	       case "SpringB-Rain":
	       case "SpringB-Wind":
	       season = "春季的凌晨"; break;
	       case "SpringC-Sun":
	       case "SpringC-Rain":
	       case "SpringC-Wind":
	       season = "春末的凌晨"; break;
	       case "SummerA-Sun":
	       case "SummerA-Rain":
	       case "SummerA-Wind":
	       season = "初夏的凌晨"; break;
	       case "SummerB-Sun":
	       case "SummerB-Rain":
	       case "SummerB-Wind":
	       season = "盛夏的凌晨"; break;
	       case "SummerC-Sun":
	       case "SummerC-Rain":
	       case "SummerC-Wind":
	       season = "夏末的凌晨"; break;
	       case "AutumnA-Sun":
	       case "AutumnA-Rain":
	       case "AutumnA-Wind":
	       season = "初秋的凌晨"; break;
	       case "AutumnB-Sun":
	       case "AutumnB-Rain":
	       case "AutumnB-Wind":
	       season = "秋季的凌晨"; break;
	       case "AutumnC-Sun":
	       case "AutumnC-Rain":
	       case "AutumnC-Wind":
	       season = "深秋的凌晨"; break;
	       case "WinterA-Sun":
	       case "WinterA-Snow":
	       case "WinterA-Wind":
	       season = "初冬的凌晨"; break;
	       case "WinterB-Sun":
	       case "WinterB-Snow":
	       case "WinterB-Wind":
	       season = "隆冬的凌晨"; break;
	       case "WinterC-Sun":
	       case "WinterC-Snow":
	       case "WinterC-Wind":
	       season = "冬末的凌晨"; break;
	       case "Default-Sun":
	       season = "晴朗的凌晨"; break;
		default: // 凌晨缺省时的描述
	       season = "晴朗的凌晨";
       }
	}

      if( day_event() == "event_sunrise" ) {
       switch (get_season) {
	       case "SpringA-Sun":
	       case "SpringA-Rain":
	       case "SpringA-Wind":
	       season = "初春的早晨"; break;
	       case "SpringB-Sun":
	       case "SpringB-Rain":
	       case "SpringB-Wind":
	       season = "春季的早晨"; break;
	       case "SpringC-Sun":
	       case "SpringC-Rain":
	       case "SpringC-Wind":
	       season = "春末的早晨"; break;
	       case "SummerA-Sun":
	       case "SummerA-Rain":
	       case "SummerA-Wind":
	       season = "初夏的早晨"; break;
	       case "SummerB-Sun":
	       case "SummerB-Rain":
	       case "SummerB-Wind":
	       season = "盛夏的早晨"; break;
	       case "SummerC-Sun":
	       case "SummerC-Rain":
	       case "SummerC-Wind":
	       season = "夏末的早晨"; break;
	       case "AutumnA-Sun":
	       case "AutumnA-Rain":
	       case "AutumnA-Wind":
	       season = "初秋的早晨"; break;
	       case "AutumnB-Sun":
	       case "AutumnB-Rain":
	       case "AutumnB-Wind":
	       season = "秋季的早晨"; break;
	       case "AutumnC-Sun":
	       case "AutumnC-Rain":
	       case "AutumnC-Wind":
	       season = "深秋的早晨"; break;
	       case "WinterA-Sun":
	       case "WinterA-Snow":
	       case "WinterA-Wind":
	       season = "初冬的早晨"; break;
	       case "WinterB-Sun":
	       case "WinterB-Snow":
	       case "WinterB-Wind":
	       season = "隆冬的早晨"; break;
	       case "WinterC-Sun":
	       case "WinterC-Snow":
	       case "WinterC-Wind":
	       season = "冬末的早晨"; break;
	       case "Default-Sun":
	       season = "晴朗的早晨"; break;
		default: // 早晨缺省时的描述
	       season = "晴朗的早晨";
       }
	}

      if( day_event() == "event_morning" ) {
       switch (get_season) {
	       case "SpringA-Sun":
	       case "SpringA-Rain":
	       case "SpringA-Wind":
	       season = "初春的上午"; break;
	       case "SpringB-Sun":
	       case "SpringB-Rain":
	       case "SpringB-Wind":
	       season = "春季的上午"; break;
	       case "SpringC-Sun":
	       case "SpringC-Rain":
	       case "SpringC-Wind":
	       season = "春末的上午"; break;
	       case "SummerA-Sun":
	       case "SummerA-Rain":
	       case "SummerA-Wind":
	       season = "初夏的上午"; break;
	       case "SummerB-Sun":
	       case "SummerB-Rain":
	       case "SummerB-Wind":
	       season = "盛夏的上午"; break;
	       case "SummerC-Sun":
	       case "SummerC-Rain":
	       case "SummerC-Wind":
	       season = "夏末的上午"; break;
	       case "AutumnA-Sun":
	       case "AutumnA-Rain":
	       case "AutumnA-Wind":
	       season = "初秋的上午"; break;
	       case "AutumnB-Sun":
	       case "AutumnB-Rain":
	       case "AutumnB-Wind":
	       season = "秋季的上午"; break;
	       case "AutumnC-Sun":
	       case "AutumnC-Rain":
	       case "AutumnC-Wind":
	       season = "深秋的上午"; break;
	       case "WinterA-Sun":
	       case "WinterA-Snow":
	       case "WinterA-Wind":
	       season = "初冬的上午"; break;
	       case "WinterB-Sun":
	       case "WinterB-Snow":
	       case "WinterB-Wind":
	       season = "隆冬的上午"; break;
	       case "WinterC-Sun":
	       case "WinterC-Snow":
	       case "WinterC-Wind":
	       season = "冬末的上午"; break;
	       case "Default-Sun":
	       season = "晴朗的上午"; break;
		default://上午缺省时的描述
	       season = "晴朗的上午";
       }
	}

      if( day_event() == "event_noon" ) {
       switch (get_season) {
	       case "SpringA-Sun":
	       case "SpringA-Rain":
	       case "SpringA-Wind":
	       season = "初春的正午"; break;
	       case "SpringB-Sun":
	       case "SpringB-Rain":
	       case "SpringB-Wind":
	       season = "春季的正午"; break;
	       case "SpringC-Sun":
	       case "SpringC-Rain":
	       case "SpringC-Wind":
	       season = "春末的正午"; break;
	       case "SummerA-Sun":
	       case "SummerA-Rain":
	       case "SummerA-Wind":
	       season = "初夏的正午"; break;
	       case "SummerB-Sun":
	       case "SummerB-Rain":
	       case "SummerB-Wind":
	       season = "盛夏的正午"; break;
	       case "SummerC-Sun":
	       case "SummerC-Rain":
	       case "SummerC-Wind":
	       season = "夏末的正午"; break;
	       case "AutumnA-Sun":
	       case "AutumnA-Rain":
	       case "AutumnA-Wind":
	       season = "初秋的正午"; break;
	       case "AutumnB-Sun":
	       case "AutumnB-Rain":
	       case "AutumnB-Wind":
	       season = "秋季的正午"; break;
	       case "AutumnC-Sun":
	       case "AutumnC-Rain":
	       case "AutumnC-Wind":
	       season = "深秋的正午"; break;
	       case "WinterA-Sun":
	       case "WinterA-Snow":
	       case "WinterA-Wind":
	       season = "初冬的正午"; break;
	       case "WinterB-Sun":
	       case "WinterB-Snow":
	       case "WinterB-Wind":
	       season = "隆冬的正午"; break;
	       case "WinterC-Sun":
	       case "WinterC-Snow":
	       case "WinterC-Wind":
	       season = "冬末的正午"; break;
	       case "Default-Sun":
	       season = "晴朗的正午"; break;
		default: // 正午缺省时的描述
	       season = "晴朗的正午";
       }
	}

      if( day_event() == "event_afternoon" ) {
       switch (get_season) {
	       case "SpringA-Sun":
	       case "SpringA-Rain":
	       case "SpringA-Wind":
	       season = "初春的下午"; break;
	       case "SpringB-Sun":
	       case "SpringB-Rain":
	       case "SpringB-Wind":
	       season = "春季的下午"; break;
	       case "SpringC-Sun":
	       case "SpringC-Rain":
	       case "SpringC-Wind":
	       season = "春末的下午"; break;
	       case "SummerA-Sun":
	       case "SummerA-Rain":
	       case "SummerA-Wind":
	       season = "初夏的下午"; break;
	       case "SummerB-Sun":
	       case "SummerB-Rain":
	       case "SummerB-Wind":
	       season = "盛夏的下午"; break;
	       case "SummerC-Sun":
	       case "SummerC-Rain":
	       case "SummerC-Wind":
	       season = "夏末的下午"; break;
	       case "AutumnA-Sun":
	       case "AutumnA-Rain":
	       case "AutumnA-Wind":
	       season = "初秋的下午"; break;
	       case "AutumnB-Sun":
	       case "AutumnB-Rain":
	       case "AutumnB-Wind":
	       season = "秋季的下午"; break;
	       case "AutumnC-Sun":
	       case "AutumnC-Rain":
	       case "AutumnC-Wind":
	       season = "深秋的下午"; break;
	       case "WinterA-Sun":
	       case "WinterA-Snow":
	       case "WinterA-Wind":
	       season = "初冬的下午"; break;
	       case "WinterB-Sun":
	       case "WinterB-Snow":
	       case "WinterB-Wind":
	       season = "隆冬的下午"; break;
	       case "WinterC-Sun":
	       case "WinterC-Snow":
	       case "WinterC-Wind":
	       season = "冬末的下午"; break;
	       case "Default-Sun":
	       season = "晴朗的下午"; break;
		default: // 下午缺省时的描述
	       season = "晴朗的下午";
       }
	}

      if( day_event() == "event_evening" ) {
       switch (get_season) {
	       case "SpringA-Sun":
	       case "SpringA-Rain":
	       case "SpringA-Wind":
	       season = "初春的傍晚"; break;
	       case "SpringB-Sun":
	       case "SpringB-Rain":
	       case "SpringB-Wind":
	       season = "春季的傍晚"; break;
	       case "SpringC-Sun":
	       case "SpringC-Rain":
	       case "SpringC-Wind":
	       season = "春末的傍晚"; break;
	       case "SummerA-Sun":
	       case "SummerA-Rain":
	       case "SummerA-Wind":
	       season = "初夏的傍晚"; break;
	       case "SummerB-Sun":
	       case "SummerB-Rain":
	       case "SummerB-Wind":
	       season = "盛夏的傍晚"; break;
	       case "SummerC-Sun":
	       case "SummerC-Rain":
	       case "SummerC-Wind":
	       season = "夏末的傍晚"; break;
	       case "AutumnA-Sun":
	       case "AutumnA-Rain":
	       case "AutumnA-Wind":
	       season = "初秋的傍晚"; break;
	       case "AutumnB-Sun":
	       case "AutumnB-Rain":
	       case "AutumnB-Wind":
	       season = "秋季的傍晚"; break;
	       case "AutumnC-Sun":
	       case "AutumnC-Rain":
	       case "AutumnC-Wind":
	       season = "深秋的傍晚"; break;
	       case "WinterA-Sun":
	       case "WinterA-Snow":
	       case "WinterA-Wind":
	       season = "初冬的傍晚"; break;
	       case "WinterB-Sun":
	       case "WinterB-Snow":
	       case "WinterB-Wind":
	       season = "隆冬的傍晚"; break;
	       case "WinterC-Sun":
	       case "WinterC-Snow":
	       case "WinterC-Wind":
	       season = "冬末的傍晚"; break;
	       case "Default-Sun":
	       season = "晴朗的傍晚"; break;
		default: // 傍晚缺省时的描述
	       season = "晴朗的傍晚";
       }
	}

      if( day_event() == "event_night" ) {
       switch (get_season) {
	       case "SpringA-Sun":
	       case "SpringA-Rain":
	       case "SpringA-Wind":
	       season = "初春的夜晚"; break;
	       case "SpringB-Sun":
	       case "SpringB-Rain":
	       case "SpringB-Wind":
	       season = "春季的夜晚"; break;
	       case "SpringC-Sun":
	       case "SpringC-Rain":
	       case "SpringC-Wind":
	       season = "春末的夜晚"; break;
	       case "SummerA-Sun":
	       case "SummerA-Rain":
	       case "SummerA-Wind":
	       season = "初夏的夜晚"; break;
	       case "SummerB-Sun":
	       case "SummerB-Rain":
	       case "SummerB-Wind":
	       season = "盛夏的夜晚"; break;
	       case "SummerC-Sun":
	       case "SummerC-Rain":
	       case "SummerC-Wind":
	       season = "夏末的夜晚"; break;
	       case "AutumnA-Sun":
	       case "AutumnA-Rain":
	       case "AutumnA-Wind":
	       season = "初秋的夜晚"; break;
	       case "AutumnB-Sun":
	       case "AutumnB-Rain":
	       case "AutumnB-Wind":
	       season = "秋季的夜晚"; break;
	       case "AutumnC-Sun":
	       case "AutumnC-Rain":
	       case "AutumnC-Wind":
	       season = "深秋的夜晚"; break;
	       case "WinterA-Sun":
	       case "WinterA-Snow":
	       case "WinterA-Wind":
	       season = "初冬的夜晚"; break;
	       case "WinterB-Sun":
	       case "WinterB-Snow":
	       case "WinterB-Wind":
	       season = "隆冬的夜晚"; break;
	       case "WinterC-Sun":
	       case "WinterC-Snow":
	       case "WinterC-Wind":
	       season = "冬末的夜晚"; break;
	       case "Default-Sun":
	       season = "晴朗的夜晚"; break;
		default://夜晚缺省时的描述
	       season = "晴朗的夜晚";
       }
	}

      if( day_event() == "event_midnight" ) {
       switch (get_season) {
	       case "SpringA-Sun":
	       case "SpringA-Rain":
	       case "SpringA-Wind":
	       season = "初春的午夜"; break;
	       case "SpringB-Sun":
	       case "SpringB-Rain":
	       case "SpringB-Wind":
	       season = "春季的午夜"; break;
	       case "SpringC-Sun":
	       case "SpringC-Rain":
	       case "SpringC-Wind":
	       season = "春末的午夜"; break;
	       case "SummerA-Sun":
	       case "SummerA-Rain":
	       case "SummerA-Wind":
	       season = "初夏的午夜"; break;
	       case "SummerB-Sun":
	       case "SummerB-Rain":
	       case "SummerB-Wind":
	       season = "盛夏的午夜"; break;
	       case "SummerC-Sun":
	       case "SummerC-Rain":
	       case "SummerC-Wind":
	       season = "夏末的午夜"; break;
	       case "AutumnA-Sun":
	       case "AutumnA-Rain":
	       case "AutumnA-Wind":
	       season = "初秋的午夜"; break;
	       case "AutumnB-Sun":
	       case "AutumnB-Rain":
	       case "AutumnB-Wind":
	       season = "秋季的午夜"; break;
	       case "AutumnC-Sun":
	       case "AutumnC-Rain":
	       case "AutumnC-Wind":
	       season = "深秋的午夜"; break;
	       case "WinterA-Sun":
	       case "WinterA-Snow":
	       case "WinterA-Wind":
	       season = "初冬的午夜"; break;
	       case "WinterB-Sun":
	       case "WinterB-Snow":
	       case "WinterB-Wind":
	       season = "隆冬的午夜"; break;
	       case "WinterC-Sun":
	       case "WinterC-Snow":
	       case "WinterC-Wind":
	       season = "冬末的午夜"; break;
	       case "Default-Sun":
	       season = "晴朗的午夜"; break;
		default: // 午夜缺省时的描述
	       season = "晴朗的午夜";
       }
	}


       return season;
}

// Added By waiwai@2002/12/05
// 季节前缀需要更加准确才行
string check_month_desc()
{
	string get_season;
	string month_desc;
	get_season= NATURE_D->check_seasonF();

       switch (get_season) {
	       case "SpringA-Sun":
	       case "SpringA-Rain":
	       case "SpringA-Wind":
	       month_desc = "初春的"; break;
	       case "SpringB-Sun":
	       case "SpringB-Rain":
	       case "SpringB-Wind":
	       month_desc = "春季的"; break;
	       case "SpringC-Sun":
	       case "SpringC-Rain":
	       case "SpringC-Wind":
	       month_desc = "春末的"; break;
	       case "SummerA-Sun":
	       case "SummerA-Rain":
	       case "SummerA-Wind":
	       month_desc = "初夏的"; break;
	       case "SummerB-Sun":
	       case "SummerB-Rain":
	       case "SummerB-Wind":
	       month_desc = "盛夏的"; break;
	       case "SummerC-Sun":
	       case "SummerC-Rain":
	       case "SummerC-Wind":
	       month_desc = "夏末的"; break;
	       case "AutumnA-Sun":
	       case "AutumnA-Rain":
	       case "AutumnA-Wind":
	       month_desc = "初秋的"; break;
	       case "AutumnB-Sun":
	       case "AutumnB-Rain":
	       case "AutumnB-Wind":
	       month_desc = "秋季的"; break;
	       case "AutumnC-Sun":
	       case "AutumnC-Rain":
	       case "AutumnC-Wind":
	       month_desc = "深秋的"; break;
	       case "WinterA-Sun":
	       case "WinterA-Snow":
	       case "WinterA-Wind":
	       month_desc = "初冬的"; break;
	       case "WinterB-Sun":
	       case "WinterB-Snow":
	       case "WinterB-Wind":
	       month_desc = "隆冬的"; break;
	       case "WinterC-Sun":
	       case "WinterC-Snow":
	       case "WinterC-Wind":
	       month_desc = "冬末的"; break;
	       case "Default-Sun":
	       month_desc = "晴朗的"; break;
		default://夜晚缺省时的描述
	       month_desc = "晴朗的";
       }

       return month_desc;
}
/**************************************************************************************************/


// Added By waiwai@2002/12/05
// 个人十二生肖图(唉，做的斗眼！)
// 目前图谱在USER_OB只做调用，未做Save
// 目前主要用于look others or look me
// 在LINK_OB做了Save Set，在Quit时自动Set
// 如果异常需要玩家在chfn确定一次
// 目前主要用于finger
/*
string check_sxt(object ob)
{
	string get_sx;
	string sxt;
	mixed *local;
	// 这个方式暂时禁止
	// 原因在chinesed.c里面已经做了说明
//	get_sx = CHINESE_D->check_sx(ob);
	get_sx = ob->query("12_sx");

       switch (get_sx) {

	       case "子鼠":
	       sxt =
WHT"
 ◢"NOR BWHT WHT"▁"NOR"    "BWHT WHT"▁"NOR WHT"◣"WHT"
 █"BBLU BLK"▁"NOR BWHT CYN"▏"NOR BWHT BLK" ."NOR BBLU HIW"◣"NOR BWHT BLK"▁"NOR"
    "BWHT"▁▁▁"HIR"="NOR HIR"@="HIW"
| ◢"BBLU"◤  ◥"NOR HIW"◣
 \\ "NOR BYEL" "NOR BBLU WHT"  ×  "NOR BYEL" "NOR"
 "BWHT BLK"◢"NOR BLK BWHT"█▃▃█◣"NOR"    [生肖]：子鼠
"; break;

	       case "丑牛":
	       sxt =
HIY"
 ◢        ◣
 ◥"BYEL HIY"◤    ◥"NOR HIY"◤"NOR YEL"
◥◤"NOR BYEL BLK" .  . "NOR YEL"◥◤"HIW"
  ◢"BWHT HIR" ︵︵ "NOR HIW"◣"NOR"
  "BWHT YEL"_▁"NOR" "BWHT YEL"▁"NOR" "BWHT YEL"▁_"NOR HIY"
    ◥"NOR BRED HIY"▁"NOR HIY"◤"NOR"       [生肖]：丑牛
"; break;

	       case "寅虎":
	       sxt =
YEL"
   ◣  ◢
 ◢"BYEL BLK" .~~. "NOR YEL"◣
◢"NOR BYEL BLK"≡"BWHT RED"◥◤"BYEL BLK"≡"NOR YEL"◣"HIY"
 ◥"BWHT HIY"◣"BLK"∣"BWHT HIY"◢"NOR HIY"◤"HIW"
 ◢"HIY"▆"BYEL"  "NOR HIY"▆"HIW"◣
 ``"NOR BYEL YEL"▆"BLK BYEL"×"NOR BYEL YEL"▆"NOR HIW"''"NOR"    [生肖]：寅虎
"; break;

	       case "卯兔":
	       sxt =
HIW"
  ◢█  █◣"NOR"
    "BWHT RED"▌"NOR"  "BRED WHT"▌"NOR HIW"
  ◢"NOR BWHT YEL"▔"HIR".."NOR BWHT YEL"▔"NOR HIW"◣
  ◢"NOR BWHT HIR"≡●≡"NOR HIW"◣
   ("NOR BMAG YEL"▕"NOR BWHT YEL"∣"NOR BMAG YEL"▏"NOR HIW")
◢"NOR BWHT YEL"▕"NOR BMAG HIW",,"NOR"  "BMAG HIW",,"NOR BWHT YEL"▏"NOR HIW"◣"NOR"    [生肖]：卯兔
"; break;

	       case "辰龙":
	       sxt =
HIY"
   ◢    ◣
   ◥◣◢◤
  ◥"NOR BYEL" "NOR BWHT BLK".\\/."NOR BYEL" "NOR HIY"◤
 "HIR"__"HIY"◥"NOR BWHT BLK" ≡ "NOR HIY"◤"HIR"__
"HIC"◢"BCYN"◣"NOR HIY"◥"NOR BWHT".."NOR HIY"◤"NOR HIC BCYN"◢"NOR HIC"◣
"HIW"▼▼"HIY"﹋  ﹋"HIW"▼▼"NOR"    [生肖]：辰龙
"; break;

	       case "巳蛇":
	       sxt =
HIR"
  ∩
"HIW"◢"NOR BWHT"   "NOR HIW"◣"NOR RED"  ╲
"HIR"` /"NOR WHT"◤"RED"◥"BWHT"╲"NOR WHT"◣"NOR RED"╲
       ◥"NOR BWHT"╲"NOR RED"  ▎
 ◢"NOR BGRN RED"◥"NOR GRN"◣"NOR WHT"◢"RED"◤  ▌
 "HIW"◥"NOR BWHT RED"◣◣"NOR BGRN RED"◤ ◣"RED"◤"NOR"     [生肖]：巳蛇
"; break;

	       case "午马":
	       sxt =
"    "BRED" "NOR WHT"◣  ◢"NOR BRED" "NOR"
    "HIW"◢"HIB"██"HIW"◣
    "NOR BLU BWHT"  .◥.  "NOR"
 "BRED WHT"▅"NOR WHT" ◥"NOR BWHT BLK"＿＿"NOR WHT"◤ "NOR BRED WHT"▅"NOR"
 "HIW"■ ◢"NOR BWHT BLK" oo "NOR HIW"◣ ■"NOR"
 "HIW"◥ ◥"NOR BWHT HIR"▃▃"NOR HIW"◤ ◤"NOR"     [生肖]：午马
"; break;

	       case "未羊":
	       sxt =
CYN"
   ◢◢"HIW"
 ◢"BWHT BLK" . "NOR HIW"◣"NOR"
 "BWHT RED"〞    "NOR HIW"
  ◢"NOR BWHT BLK"╱    "NOR HIW"◣/"NOR"
  "BWHT BLK"▕  ▁"NOR HIW"
  ◤◤ ◥ ◥"NOR"    [生肖]：未羊
"; break;

	       case "申猴":
	       sxt =
HIY"
   ◢"BYEL HIW"▄▄"NOR HIY"◣"NOR"
  "HIW"("NOR BWHT BLK"  .  .  "NOR HIW")"NOR"
  "BYEL BLK"▔"NOR BWHT BLK" /..\\ "BYEL"▔"NOR"
  "HIY"◥"NOR BWHT HIR" (＝) "NOR HIY"◤"NOR"
  "HIY"█"NOR BWHT BLK"▏  ▕"NOR HIY"█"NOR"
  "HIY"◥"NOR BWHT HIY"◣"BLK"×"HIY"◢"NOR HIY"◤"HIR"~~~"NOR"    [生肖]：申猴
"; break;

	       case "酉鸡":
	       sxt =
"
 "HIR"◥◣◣"NOR"
 "HIY"◢"HBWHT BLK".   "NOR"  "WHT"◢◣
  "HBWHT HIR"▉ "NOR HIW"◤◢█◣"NOR"
   "HBWHT BLK"▕,,▕"NOR HIW"▇◥
   ◥"HBWHT BLK"▔▔"NOR HIW"◤"HIY"
      ⊥"NOR"      [生肖]：酉鸡
"; break;

	       case "戌狗":
	       sxt =
HIW"
  ,,,,"NOR"
  "BWHT BLK" ."RED"▇"NOR"
"BWHT BLK"〞  "HIR"◥"NOR HIW"    ◢"NOR"
  "HIW"◢█◣◢◣"NOR"
  "BWHT BLK" ∣ ▁▁  "NOR"
  "HIW"◤◤  ◥◥"NOR"    [生肖]：戌狗
"; break;

	       case "亥猪":
	       sxt =
HIW"
◢◣   ◢◣"NOR"
 "HIW"▇"NOR BWHT BLK".___."NOR HIW"▇"NOR"
"HIW"◢"NOR HIY BWHT"◢"NOR BYEL YEL"▌ "NOR HIY BWHT"◣"NOR HIW"◣"NOR"
"HIW"◥"NOR BWHT HIR" ◥"NOR BRED HIG"_"NOR BWHT HIR"◤ "NOR HIW"◤"NOR"
"HIY"◢"NOR BWHT HIY"◣"BLK"___"HIY"◢"NOR HIY"◣"NOR"
"HIW"◤◥   ◤◥"NOR"    [生肖]：亥猪
"; break;

		default:
	       sxt = "";
       }

       return sxt;
}
*/
/**************************************************************************************************/

//Added By waiwai@2002/12/05
//个人十二星座图(头大了，暂时不做了)
string check_xzt(object ob)
{
	string get_xz;
	string xzt;
	mixed *local;
	get_xz = ob->query("12_xz");
}

//纯数字格式，中文格式在Combated.c
//里面COMBAT_D->chinese_daoxing()
string check_daoxing(int gain)
{            int year,day,hour;
             string str;

             year=gain/1000;
             day=(gain-year*1000)/4;
             hour=(gain-year*1000-day*4)*3;
             str="";
             if(year) str=str+(year)+"年";
             if(day) str=str+(day)+"天";
             if(hour) str=str+(hour)+"时辰";

             return str;
}

string query_time(int time)
{
        string msg;
        int day, hour, min;

        time=time()-time;

        msg="";
        day=time/86400;
        hour=time%86400/3600;
        min=time/60%60;

        if(min<1)
                min=1;
        if(day)
                msg+=sprintf("%d天", day);
        if(day<10 && hour)
                msg+=sprintf("%d小时", hour);
        if(!day && hour<20 && min )
                msg+=sprintf("%d分钟", min);

        return msg;
}

string query_timec(int time)
{
        string msg;
        int day, hour, min;

        time=time()-time;

        msg="";
        day=time/86400;
        hour=time%86400/3600;
        min=time/60%60;
        if(min<1)
                min=1;
        if(day)
                msg+=sprintf("%s天", chinese_number(day));
        if(day<10 && hour)
                msg+=sprintf("%s小时", chinese_number(hour));
        if(!day && hour<20 && min)
                msg+=sprintf("%s分钟", chinese_number(min));
        return msg;
}

string report_str(int temp)
{
	int t, d, h, m, s;
	string time;
	if( !temp )
		temp = time();
	t = temp;
	s = t % 60;		t /= 60;
	m = t % 60;		t /= 60;
	h = t % 24;		t /= 24;
	d = t;

	if(d) time = chinese_number(d) + "天";
	else time = "";

	if(h) time += chinese_number(h) + "小时";
	if(m) time += chinese_number(m) + "分";
	time += chinese_number(s) + "秒";

	return(time);
}

string report_str_e(int temp)
{
	int t, d, h, m, s;
	string time;

	t = temp;
	s = t % 60;		t /= 60;
	m = t % 60;		t /= 60;
	h = t % 24;		t /= 24;
	d = t;

	if(d) time = (string)(d) + "天";
	else time = "";

	if(h) time += (string)(h) + "小时";
	if(m) time += (string)(m) + "分";
	time += (string)(s) + "秒";

	return(time);
}

/**************************************************************************************************/
// added by jingxue 12.25.2004 计算所有公历之节日
// type为2 返回星期几的中文
// 其余type 返回节日的中文
string query_gala(int type)
{
	string gala, get_time, e_time, week, month, year;
	int day, hour, minute, second, n_month;
        string *month_name = ({"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"});
        string *week_name = ({"Mon","Tue","Wed","Thu","Fri","Sat","Sun"});

        get_time = (string)localtime(time());
        if ( stringp(get_time) )
                e_time = get_time;
        else e_time = ctime(time());
        sscanf(e_time,"%s %s %d %d:%d:%d %s", week, month, day, hour, minute, second, year);

        week  = chinese_number(member_array(week, week_name) + 1);

        n_month = member_array(month, month_name) + 1;

// type为2 返回星期几的中文。
	if (type == 2)
		return week;

// 农历节日
	if (GALA_C != "无" && GALA_C != "无节日") gala = GALA_C;

// 公历节日
	else if (n_month == 1 && day == 1) gala = "元旦节";
	else if (n_month == 2 && day == 14) gala = "情人节";
	else if (n_month == 5 && day == 1) gala = "五一劳动节";
	else if (n_month == 6 && day == 1) gala = "六一儿童节";
	else if (n_month == 10 && day == 1) gala = "国庆节";
	else if (n_month == 12 && day == 25) gala = "圣诞节";
	else gala = "无节日";

	return gala;
}

/**************************************************************************************************/
// added by jingxue 12.25.2004
// 计算让节日是否给予双倍或者多倍奖励
// 系统遇到节日将给予双倍奖励
// 巫师需要提高奖励只需要修改经验基数DOUBLE_REWARD
// 节日经验系数一般为200，也就是经验双倍200%
// 经验基数DOUBLE_REWARD为100则为正常值，也就是经验将为100%
// type为奖励类型
// type为1则只按普通比例奖励，不考虑节日系数和经验基数
// type为2则只考虑节日系数，不考虑经验基数
// type为3则不考虑节日系数，只考虑经验基数
// type为4则既考虑节日系数，又考虑经验基数
int query_double_reward(int type)
{
	string gala;
	int report_reward_w, report_reward_g;

        gala = (string)query_gala(1);
        if (gala != "无" && gala != "无节日")
        	report_reward_g = 200;
	else
		report_reward_g = 100;
       	report_reward_w = DOUBLE_REWARD;

        if (type)
        {
                switch( type )
                {
                        case 1: return 100;
                        case 2: return report_reward_g;
                        case 3: return report_reward_w;
                        case 4: return (report_reward_g * report_reward_w) /100;
                        default: return 100;
		}
	}
	return 100;
}

/**************************************************************************************************/

/*
public int record_rumor(mixed obs, string topic, mixed event_ob)
{
        object ob;
        string title;
        int n;

        if (objectp(obs)) obs = ({ obs }); else
        if (! arrayp(obs)) return 0;

        if (! stringp(title = event_ob->query_detail(topic)))
                return 0;

        if (stringp(event_ob)) event_ob = base_name(find_object(event_ob)); else
                               event_ob = base_name(event_ob);
        n = 0;
        foreach (ob in obs) {
                if (! playerp(ob) || ! ob->query("out_family")) continue;
                if (ob->query("rumor/" + topic)) continue;
                ob->set("rumor/" + topic, event_ob);
                message("vision", "你掏出地图册，翻到最后面，写下了有关『" +
                                  topic + "』的记录。\n", ob);
                n++;
        }

        return n;
}
*/

string chinese_time(string get_time)
{
        string e_time, week, month, year;
        string c_week, c_year, c_month, c_time;
        int day, hour, minute, second;
        string *month_name = ({"Jan","Feb","Mar","Apr","May","Jun","Jul",
                "Aug","Sep","Oct","Nov","Dec"});
        string *week_name = ({"Mon","Tue","Wed","Thu","Fri","Sat","Sun"});

        if( stringp(get_time) )
                e_time = get_time;
        else    e_time = ctime(time());
        sscanf(e_time,"%s %s %d %d:%d:%d %s", week, month, day, hour, minute, second, year);

        c_week  = chinese_number(member_array(week, week_name) + 1);
        c_month = chinese_number(member_array(month, month_name) + 1);
        c_year  = sprintf("%s%s%s%s",
                         chinese_number(year[0]-48),
                         chinese_number(year[1]-48),
                         chinese_number(year[2]-48),
                         chinese_number(year[3]-48));
        c_year = c_year + "年";
        c_month  = c_month + "月";
        c_week = " 星期"+c_week;
        c_time = chinese_number(day) + "日";
        c_time += chinese_number(hour) + "点";
        c_time += chinese_number(minute) + "分";
        // maybe not need srcond to show
        c_time += chinese_number(second) + "秒";
        return replace_string(sprintf("%s/%2d/%2d", year, (member_array(month, month_name) + 1), day), " ", "0") + " " + e_time[11..15];
}

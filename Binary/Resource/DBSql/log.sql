/*
Navicat MySQL Data Transfer

Source Server         : MetalServer
Source Server Version : 50173
Source Host           : localhost:3306
Source Database       : metal

Target Server Type    : MYSQL
Target Server Version : 50173
File Encoding         : 65001

Date: 2014-03-26 15:58:46
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for game_account
-- ----------------------------
DROP TABLE IF EXISTS `game_account`;
CREATE TABLE `game_account` (
  `account` varchar(50) NOT NULL UNIQUE DEFAULT '' COMMENT 'account',
  `accountid` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '账号id,自增',
  `lastlogintime` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '上次登录时间',
  `create_time` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '创建帐号时间',
  `deveice` varchar(100) NOT NULL DEFAULT '' COMMENT '设备标识',
  `channel` varchar(50) NOT NULL DEFAULT '' COMMENT '渠道',
  `sub_channel` varchar(50) NOT NULL DEFAULT '' COMMENT '子渠道',
  PRIMARY KEY (`accountid`),
  index index_account (account)
) ENGINE=InnoDB AUTO_INCREMENT=73 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for game_character
-- ----------------------------
DROP TABLE IF EXISTS `game_character`;
CREATE TABLE `game_character` (
  `accountid` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '账号id',
  `guid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'guid',
  `charname` varchar(50) NOT NULL DEFAULT '' COMMENT '角色名',
  `partnerguid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '主伙伴guid',
  `level` int(20) unsigned NOT NULL DEFAULT '1' COMMENT '等级',
  `configid` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '配置id',
  `camp` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '阵营',
  `staff` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '职业',
  `create_time` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '创建角色时间',
  `last_login_time` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色上次登录时间',
  `last_update_time` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色上次更新数据时间',
  `level_reward_index` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '等级奖励索引',
  `loginfirst` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '首次登录标记',
  `battlefirst` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '首次登录标记',
  `shouchong` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '首充标记',
  `combat_value` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '战斗力',
  `guide_id` int(11) NOT NULL DEFAULT '0' COMMENT '新手引导ID',
  `guide_subid` int(11) NOT NULL DEFAULT '0' COMMENT '新手引导子ID',
  `gamemoney` int(20) unsigned NOT NULL DEFAULT '0' COMMENT '游戏币',
  `gold` int(20) NOT NULL DEFAULT '0' COMMENT '元宝数',
  `power` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '体力',
  `reputation` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '声望',
  `knowledge` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '阅历',
  `allcostgold` int(20) NOT NULL DEFAULT '0' COMMENT '总充值元宝数',
  `viplevel` int(20) unsigned NOT NULL DEFAULT '0' COMMENT 'Vip等级',
  `vip_pack` blob NOT NULL COMMENT '已购买VIP礼包',
  `buypowertimes` int(20) unsigned NOT NULL DEFAULT '0' COMMENT '本日购买体力次数',
  `buygamemoneytimes` int(20) unsigned NOT NULL DEFAULT '0' COMMENT '本日购买灵石次数',
  `buymoneybojilevel` tinyint(5) unsigned NOT NULL DEFAULT '2' COMMENT '本日购买灵石暴击等级',
  `buyarenatimes` int(20) unsigned NOT NULL DEFAULT '0' COMMENT '本日购买竞技次数',
  `buyhfbtimes` int(20) unsigned NOT NULL DEFAULT '0' COMMENT '本日购买英雄副本次数',
  `taskdata` blob NOT NULL COMMENT '任务数据',
  `building` blob NOT NULL COMMENT '建筑数据',
  `lastofflinetime` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '上次下线时间',
  `lastpowertime` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '上次体力恢复时间',
  `findtimes` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '今日已搜索次数',
  `buyfind` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '今日已购搜索次数',
  `findround` tinyint(5) unsigned NOT NULL DEFAULT '1' COMMENT '当前搜索轮次',
  `lastfindtime` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '上次出巡恢复时间',
  `xianfa` blob NOT NULL COMMENT '仙法数据',
  `fuben` blob NOT NULL COMMENT '副本数据',
  `fuben_next_id` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '下个剧情ID',
  `herofuben` blob NOT NULL COMMENT '英雄副本数据',
  `systemdata` blob NOT NULL COMMENT '系统开启数据',
  `piecedata` blob NOT NULL COMMENT '碎片数据',
  `globalpiece` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '进阶碎片',
  `signing` blob NOT NULL COMMENT '签到数据',
  `arena_rank` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '排名',
  `arena_challengecount` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '挑战次数',
  `arena_challengetime` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '挑战时间',
  `arena_remaincdtime` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '剩余CD时间',
  `arena_totalcount` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '总场数',
  `arena_wincount` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '胜利场数',
  `arena_runningcount` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '连胜场数',
  `arena_lastrank` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '昨日排名',
  `arena_realcount` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '每日实际挑战的次数',
  `arena_best_rank` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '最佳排名',
  `jxt_freecount` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '聚仙免费次数',
  `jxt_usualcdtime` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '聚仙普抽CD时间',
  `jxt_firstusual` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '聚仙普抽首抽',
  `jxt_specialcdtime` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '聚仙特抽CD时间',
  `jxt_firstspecial` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '聚仙特抽首抽',
  `friend_powercount` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '好友赠送体力次数',
  `friend_powerlogs` blob NOT NULL COMMENT '好友赠送体力记录',
  `cb_camp` tinyint(5) NOT NULL DEFAULT '-1' COMMENT '阵营',
  `cb_exploit` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '战功',
  `cb_battle_count` int(11) unsigned NOT NULL DEFAULT '10' COMMENT '出战次数',
  `cb_running_count` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '连胜次数',
  `cb_battle` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '是否出战',
  `cb_recover_time` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '恢复时间',
  `cb_last_id` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '上次战功ID',
  `cb_last_rank` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '上次战功排名',
  `cb_last_result` tinyint(5) NOT NULL DEFAULT '0' COMMENT '上次战役胜负',
  `cb_total_count` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '本场战役战斗总次数',
  `cb_win_count` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '本场战役战胜总次数',
  `cb_report_data` blob NOT NULL COMMENT '战役战报数据',
  `jt_legio_id` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '军团guid',
  `jt_legio_post` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '军团职位',
  `jt_legio_credit` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '军团贡献',
  `jt_legio_total_credit` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '累积军团总贡献',
  `jt_entry_time` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '入团时间',
  `jt_vote_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '所投票玩家ID',
  `jt_manifesto` varchar(500) NOT NULL DEFAULT '' COMMENT '军团竞选宣言',
  `jt_store_data` blob NOT NULL COMMENT '军团商店数据',
  `jt_store_next_time` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '军团商店下次刷新时间',
  `jt_book_count` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '军团读书次数',
  `jt_worship_type` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '军团供奉类型',
  `jt_accredit_data` blob NOT NULL COMMENT '军团派驻伙伴列表',
  `jt_rent_guid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '租用军团伙伴的guid',
  `jt_campaign` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '是否竞选',
  `jt_god_cd` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '天神CD时间',
  `jt_war_reward` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '军团战奖励标记',
  `formation` blob NOT NULL COMMENT '军阵数据',
  `plus_attr` blob NOT NULL COMMENT '增益数据',
  `mingge` blob NOT NULL COMMENT '命格数据',
  `lieming` blob NOT NULL COMMENT '命格临时数据',
  `onlinereward` blob NOT NULL COMMENT '在线奖励数据',
  `xzsdata` blob NOT NULL COMMENT '小助手数据',
  `zxtstar` int(11) signed NOT NULL DEFAULT '-1' COMMENT '占星台星数',
  `loginreward` blob NOT NULL COMMENT '登录奖励数据',
  `fengshen` blob NOT NULL COMMENT '封神榜数据',
  `fabao` blob NOT NULL COMMENT '法宝数据',
  `heishi` blob NOT NULL COMMENT '黑市数据',
  `jieluedata` blob NOT NULL COMMENT '劫掠数据',
  `freeze` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '封停时间',
  `islock` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '是否被锁',
  `stop_talk_time` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '禁言结束时间',
  `rechargedata` blob NOT NULL COMMENT '充值奖励数据',
  `buffbag` blob NOT NULL COMMENT 'buff数据',
  `jbp_free_count` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '聚宝盆免费次数',
  `jbp_first_flag` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '聚宝盆首抽',
  `sharing_month` int(11) signed NOT NULL DEFAULT '-1' COMMENT '分享的月份',
  `sharing_daily_cnt` int(11) signed NOT NULL DEFAULT '0' COMMENT '每日分享次数',
  `sharing_monthly_cnt` int(11) signed NOT NULL DEFAULT '0' COMMENT '每月分享次数',
  `sharing_marks` blob NOT NULL COMMENT '分享奖励领取标记',
  `jt_store_refresh` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '军团商店刷新次数',
  `offline_cost_gold` int(20) NOT NULL DEFAULT '0' COMMENT '离线充值元宝',
  PRIMARY KEY (`guid`),
  index index_guid (guid),
  index index_accountid (accountid),
  index index_arena_rank(arena_rank),
  index index_legio_id(jt_legio_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for game_item
-- ----------------------------
DROP TABLE IF EXISTS `game_item`;
CREATE TABLE `game_item` (
  `charguid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色guid',
  `guid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '装备guid',
  `itemid` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '配置id',
  `count` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '物品数量',
  `itemdata` blob NOT NULL COMMENT '各种物品数据(不含身上装备)',
  `bagtype` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '背包类型',
  PRIMARY KEY (`guid`),
  index index_charguid (charguid)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for game_partner
-- ----------------------------
DROP TABLE IF EXISTS `game_partner`;
CREATE TABLE `game_partner` (
  `charguid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色guid',
  `guid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '伙伴guid',
  `configid` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '配置id',
  `level` int(20) unsigned NOT NULL DEFAULT '1' COMMENT '等级',
  `exp` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '经验',
  `pos` tinyint(5) NOT NULL DEFAULT '0' COMMENT '出阵的位置',
  `slotid` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '上阵位置id',
  `star` tinyint(5) NOT NULL DEFAULT '0' COMMENT '星级',
  `trainstep` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '训练阶数',
  `traingrade` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '训练段位',
  `pill` blob NOT NULL COMMENT '丹药数据',
  `peiyang` blob NOT NULL COMMENT '培养数据',
  `zxlevel` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '占星等级',
  `combat_value` int(11) NOT NULL DEFAULT '0' COMMENT '战力',
  PRIMARY KEY (`guid`),
  index index_charguid (charguid)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for game_battle_pos
-- ----------------------------
DROP TABLE IF EXISTS `game_battle_slot`;
CREATE TABLE `game_battle_slot` (
  `charguid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色guid',
  `slotid` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '上阵位置id',
  `isopen` tinyint(1) unsigned NOT NULL DEFAULT '0' COMMENT '上阵格子是否开启',
  `partner_guid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '伙伴guid',
  `pos` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '队形位置',
  `equips` blob NOT NULL COMMENT '上阵位置装备',
  `mingge` blob NOT NULL COMMENT '上阵位置命格',
  index index_charguid (charguid)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for game_friend
-- ----------------------------
DROP TABLE IF EXISTS `game_friend`;
CREATE TABLE `game_friend` (
  `userguid1` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '用户1Guid',
  `userguid2` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '用户2Guid',
  `friend_status` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '好友关系',
  `request_time` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '好友申请时间',
  `power_status1` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '用户1体力赠送状态',
  `power_status2` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '用户2体力赠送状态',
  index index_guid1 (userguid1),
  index index_guid2 (userguid2)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for game_cb_partner
-- ----------------------------
DROP TABLE IF EXISTS `game_cb_partner`;
CREATE TABLE `game_cb_partner` (
  `charguid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '用户Guid',
  `configid` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '配置id',
  `level` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '等级',
  `star` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '星级',
  `pos` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '位置',
  `life` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '生命',
  `preAtk` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '先攻',
  `phisicalAtk` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '武力攻击',
  `phisicalDef` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '武力防御',
  `magicAtk` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '法力攻击',
  `magicDef` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '法力防御',
  `trickAtk` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '绝招攻击',
  `trickDef` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '绝招防御',
  `hit` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '命中等级',
  `dodge` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '闪避等级',
  `critRate` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '暴击等级',
  `tough` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '韧性等级',
  `parry` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '格挡等级',
  `break` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '破防等级',
  `anger` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '怒气初始值',
  `angerMax` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '怒气上限',
  `angerRise` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '怒气恢复值',
  `attackRange` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '攻击范围',
  index index_charguid (charguid)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for game_fabao
-- ----------------------------
DROP TABLE IF EXISTS `game_fabao`;
CREATE TABLE `game_fabao` (
  `charguid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色guid',
  `guid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '法宝guid',
  `configid` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '配置id',
  `level` int(20) unsigned NOT NULL DEFAULT '1' COMMENT '等级',
  `exp` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '经验',
  `pos` tinyint(5) NOT NULL DEFAULT '0' COMMENT '法宝装备的位置',
  `piece` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '法宝碎片数',
  PRIMARY KEY (`guid`),
  index index_charguid (charguid)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for game_legio
-- ----------------------------
DROP TABLE IF EXISTS `game_legio`;
CREATE TABLE `game_legio` (
  `legio_id` int(11) unsigned NOT NULL AUTO_INCREMENT COMMENT '军团guid',
  `legio_name` varchar(50) NOT NULL UNIQUE DEFAULT '' COMMENT '军团名称',
  `legio_level` int(11) unsigned NOT NULL DEFAULT '1' COMMENT '军团等级',
  `legio_exp` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '军团经验',
  `legio_supply` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '军团物资',
  `legio_player_count` int(11) unsigned NOT NULL DEFAULT '1' COMMENT '玩家总数',
  `legio_confine_flag` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '申请限制标记',
  `legio_confine_level` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '申请限制等级',
  `legio_apply_list` blob NOT NULL COMMENT '玩家申请列表',
  `legio_impeach_step` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '弹劾步骤',
  `legio_chief_day` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '首领离线天数',
  `legio_officer_day` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '官员离线天数',
  `legio_no_logio_day` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '无人登录天数',
  `legio_vote_day` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '投票天数',
  `legio_create_time` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '创建时间',
  `legio_notice` varchar(1000) NOT NULL DEFAULT '' COMMENT '军团公告',
  `legio_policy` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '军团方针',
  `legio_god_count` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '每周天神次数',
  `legio_god_step` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '天神步骤',
  `legio_god_type` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '天神类型',
  `legio_god_level` int(11) unsigned NOT NULL DEFAULT '1' COMMENT '天神等级',
  `legio_god_health` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '天神剩余生命值',
  `legio_god_ranking` blob NOT NULL COMMENT '天神伤害排名',
  `legio_god_bosslist` blob NOT NULL COMMENT '每日可选天神列表',
  `legio_city_id` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '军团城池ID',
  `legio_war_plan` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '军团战方针',
  `legio_war_city` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '军团方针指定城池',
  `legio_war_legio` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '军团方针指定军团',
  `legio_war_result` int(11) unsigned NOT NULL DEFAULT '0' COMMENT '军团战结果',
  `legio_tablet_level` int(11) unsigned NOT NULL DEFAULT '1' COMMENT '界碑等级',
  `legio_specialty` blob NOT NULL COMMENT '城池特产数据',  
  PRIMARY KEY (`legio_id`),
  index index_legio_name (legio_name)
) ENGINE=InnoDB AUTO_INCREMENT=10001 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for app_payment
-- ----------------------------
DROP TABLE IF EXISTS `app_payment`;
CREATE TABLE `app_payment` (
  `transaction_id` varchar(30) NOT NULL DEFAULT '' COMMENT '交易ID',
  `product_id` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '产品ID',
  `quantity` tinyint(5) unsigned NOT NULL DEFAULT '0' COMMENT '数量',
  `guid` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '角色guid',
  `finish_time` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '完成验证时间',
  index index_transaction_id (transaction_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table Structure for the game_jielue_danyao : 
-- ----------------------------

DROP TABLE IF EXISTS `game_jielue_danyao`;
CREATE TABLE `game_jielue_danyao` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `charguid` bigint(20) NOT NULL,
  `configid` int(11) NOT NULL,
  `piece` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table Structure for the soha_order : 
-- ----------------------------

DROP TABLE IF EXISTS `soha_order`;
CREATE TABLE `soha_order` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `charguid` bigint(20) NOT NULL,
  `orderid` varchar(100) NOT NULL,
  `order_info` varchar(100) NOT NULL,
  `app_id` varchar(100) NOT NULL,
  `pay_time` bigint(20) NOT NULL,
  `user_id` char(50) NOT NULL,
  `role_id` char(50) NOT NULL,
  `area_id` char(50) NOT NULL,
  `price` int(11) NOT NULL,
  `status` int(11) NOT NULL,
  `platform` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table Structure for the `game_kfz_guess` : 
-- ----------------------------
DROP TABLE IF EXISTS `game_kfz_guess`;
CREATE TABLE `game_kfz_guess` (
  `guid` bigint(20) NOT NULL,
  `cost` int(11) NOT NULL DEFAULT '0',
  `guessdata` blob NOT NULL,
  PRIMARY KEY (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
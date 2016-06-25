/*
最上层的全局数据服务器,相当于是平台
Navicat MySQL Data Transfer

Source Server         : global
Source Server Version : 5.6.17
Source Host           : localhost:3306
Source Database       : global

Target Server Type    : MYSQL
Target Server Version : 5.6.17

Date: 2016-04-06 18:00:00  utf8 latin1
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for tbl_gb_account
-- ----------------------------
DROP TABLE IF EXISTS tbl_gb_account;
CREATE TABLE tbl_gb_account(
	account_id		int(10) 		unsigned NOT NULL AUTO_INCREMENT 		COMMENT '全局账号id,自增',
	account 			varchar(50) NOT NULL DEFAULT '' 								COMMENT '帐号',
	password 			varchar(50) NOT NULL DEFAULT '' 								COMMENT '密码',
	mail		 			varchar(50) NOT NULL DEFAULT '' 								COMMENT '邮箱',
	identity_card	varchar(50) NOT NULL DEFAULT '' 								COMMENT '身份证',
	nickname			varchar(50) NOT NULL DEFAULT '' 								COMMENT '昵称',
	gender				int(11) 		unsigned NOT NULL DEFAULT '0' 			COMMENT '性别'
	create_time 	bigint(20) 	unsigned NOT NULL DEFAULT '0' 			COMMENT '创建时间',
	freeze				bigint(20)  unsigned NOT NULL DEFAULT '0' 			COMMENT '封停时间,普通玩家为0',
	image					blob 				NOT NULL 														COMMENT '头像',
	PRIMARY KEY (account_id),
  index index_account_id (account_id)
) ENGINE=InnoDB AUTO_INCREMENT=523 DEFAULT CHARSET=utf8;
-- ----------------------------
-- Table structure for tbl_game_one
-- ----------------------------
DROP TABLE IF EXISTS tbl_game_one;
CREATE TABLE tbl_game_one(
	game_account_id 	int(10) unsigned NOT NULL AUTO_INCREMENT				COMMENT '游戏帐号ID,自增',
	account_id 				int(10) unsigned NOT NULL UNIQUE DEFAULT '0'		COMMENT 'tbl_gb_account的account_id',	
	game_area_id			int(11) unsigned NOT NULL DEFAULT '0' 					COMMENT '游戏数据库分配的id,_game.sql前的编号',
	PRIMARY KEY (game_account_id),
  index index_account_id (account_id)
) ENGINE=InnoDB AUTO_INCREMENT=523 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for tbl_gb_friend
-- ----------------------------
DROP TABLE IF EXISTS tbl_gb_friend;
CREATE TABLE tbl_gb_friend(
	account_id 	int(10) 		unsigned NOT NULL UNIQUE DEFAULT '0'			COMMENT 'tbl_gb_account的account_id',
	friend_data	blob				NOT NULL																	COMMENT '好友数据',
	PRIMARY KEY (account_id),
  index index_account_id (account_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


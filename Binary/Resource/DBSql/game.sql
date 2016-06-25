/*
Navicat MySQL Data Transfer

Source Server         : _game
Source Server Version : 5.6.17
Source Host           : localhost:3306
Source Database       : _game

Target Server Type    : MYSQL
Target Server Version : 5.6.17

Date: 2016-04-06 18:00:00
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for tbl_account
-- ----------------------------
DROP TABLE IF EXISTS tbl_account;
CREATE TABLE tbl_account(
	account_id						int(10) 		unsigned NOT NULL DEFAULT '0' 			COMMENT 'global的game_account_id',
	account 							varchar(50) NOT NULL DEFAULT '' 								COMMENT '帐号',
	create_time 					bigint(20) 	unsigned NOT NULL DEFAULT '0' 			COMMENT '创建帐号时间',
	last_login_time 			bigint(20) 	unsigned NOT NULL DEFAULT '0' 			COMMENT '最后登陆时间',
	PRIMARY KEY (account_id),
  index index_account_id (account_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for tbl_player
-- ----------------------------
DROP TABLE IF EXISTS tbl_player;
CREATE TABLE tbl_player(
	player_id							bigint(20)	unsigned NOT NULL DEFAULT '0' 			COMMENT '角色guid',
	account_id						varchar(50) NOT NULL DEFAULT '' 								COMMENT '帐号',
	player_name 					varchar(50) NOT NULL DEFAULT '' 								COMMENT '角色名',
	create_time 					bigint(20) 	unsigned NOT NULL DEFAULT '0' 			COMMENT '创建时间',
	level									int(10) 		unsigned NOT NULL DEFAULT '0' 			COMMENT '等级',
	PRIMARY KEY (player_id),
  index index_player_id (player_id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for tbl_buddy
-- ----------------------------
DROP TABLE IF EXISTS tbl_buddy;
CREATE TABLE tbl_buddy(
	buddy_id							bigint(20)	unsigned NOT NULL AUTO_INCREMENT		COMMENT '伙伴id,自增',
	player_id							bigint(20)	unsigned NOT NULL DEFAULT '0' 			COMMENT 'player_id',
	config_id							int(10)			unsigned NOT NULL DEFAULT '0' 			COMMENT '伙伴配置id',
	level									int(10) 		unsigned NOT NULL DEFAULT '0' 			COMMENT '等级',
	PRIMARY KEY (buddy_id),
  index index_buddy_id (buddy_id)
) ENGINE=InnoDB AUTO_INCREMENT=523 DEFAULT CHARSET=utf8;

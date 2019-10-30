# 
# Copyright (C) 2006-2008 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=njit8021xclient
PKG_RELEASE:=1
PKG_VERSION:=1.0.1
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/njit8021xclient
	SECTION:=net
	CATEGORY:=Network
	TITLE:=FZU(and ZCXY) 802.1X client
	DEPENDS:=+libpcap
endef

define Package/njit8021xclient/description
	Thanks to njit8021xclient make by liuqun.
endef

define Build/Prepare
	echo "Here is Package/Prepare"
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/njit8021xclient/install
	echo "Here is Package/install"
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/client $(1)/bin/njit-client
endef

$(eval $(call BuildPackage,njit8021xclient))


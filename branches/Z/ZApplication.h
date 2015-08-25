#ifndef __ZApplication_h__
#define __ZApplication_h__

#pragma once

#include "Z.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Z
{
	ref class ZTemplate;
	/* Application Window */
	ref class ZApplication : public System::Windows::Forms::Form
	{
		/* Append a menu item object to the Insert context menu */
		delegate void AppendInsertMenuItemCaller ( String^ name );
		/* Remove a menu item object from the Insert context menu */
		delegate void RemoveInsertMenuItemCaller ( String^ name );
		/* Remove all menu items from the Insert context menu */
		delegate void ClearInsertMenuCaller ( void );
		/* Append a ListViewItem object to a list */
		delegate void AppendItemCaller ( ListViewItem^ listViewItem );		
		/* The the text of a packet field */
		delegate void SetPacketTextCaller ( String^ text );

	private:
		/* Random number generator */
		static Random^ Randomize = gcnew Random;

	public:
		/* Constructor */
		ZApplication ( void )
		{
			InitializeComponent();
			InitializeProtections();
			InitializeCollections();
		}
		/* Dispose */
		~ZApplication ( void )
		{
			if ( components )
				delete components;
		}

	private:
		/* Lock-out certain features based on installed hooks */
		void InitializeProtections ( void );
		/* Append the necessary collection items to the menus */
		void InitializeCollections ( void );

	protected:
		virtual void OnLoad ( EventArgs^ e ) override;

		virtual void OnClosing ( CancelEventArgs^ e ) override;

		virtual void OnClosed ( EventArgs^ e ) override;

		virtual void OnShown ( EventArgs^ e ) override;

	public:
		/* Append a menu item object to the Insert context menu */
		void AppendInsertMenuItem ( String^ name );
		/* Remove a menu item object from the Insert context menu */
		void RemoveInsertMenuItem ( String^ name );
		/* Remove all menu items from the Insert context menu */
		void ClearInsertMenu ( void );

	public:
		/* Apply a template to the items of the recv and sent lists */
		void ApplyTemplate ( ZTemplate^ t );
		/* Reset items when a template is destroyed */
		void ResetTemplate ( void );
		/* Set the text of the last focused packet field */
		void SetPacketText ( String^ text );
		/* Append a ListViewItem object to the received packets list */
		void AppendRecvListItem ( ListViewItem^ listViewItem );
		/* Set the text of the receive input field */
		void SetRecvPacketText ( String^ text );
		/* Append a ListViewItem object to the sent packets list */
		void AppendSendListItem ( ListViewItem^ listViewItem );
		/* Set the text of the send input field */
		void SetSendPacketText ( String^ text );
		/* Append a ListViewItem object to the packet history list */
		void AppendHistoryListItem ( ListViewItem^ listViewItem );

	private: System::Windows::Forms::MenuStrip^  m_mbrStrip;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmMapleToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmMemoryToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  m_sprMapleMenuToolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmQuitGameToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmExitGameToolStripMenuItem;





	private: System::Windows::Forms::ToolStripSeparator^  m_sprMapleMenuToolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmExitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmPacketsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmTemplatesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmBuilderToolStripMenuItem;





	private: System::Windows::Forms::ToolStripSeparator^  m_sprPacketsMenuToolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmHistoryToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmPatternsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmBlockedRecvToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmIgnoredRecvToolStripMenuItem;





	private: System::Windows::Forms::ToolStripSeparator^  m_sprPatternsMenuToolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmBlockedSendToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmIgnoredSendToolStripMenuItem;



	private: System::Windows::Forms::ToolStripSeparator^  m_sprPatternsMenuToolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmCustomToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmCollectionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmFavoritesToolStripMenuItem;




	private: System::Windows::Forms::ToolStripMenuItem^  m_itmScriptsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmToolsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmSettingsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmAlwaysOnTopToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmTransparentToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  m_sprSettingsMenuToolStripSeparator1;






	private: System::Windows::Forms::ToolStripMenuItem^  m_itmTopLevelWindowToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmSystemTrayIconToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmMinimizeOnCloseToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  m_sprSettingsMenuToolStripSeparator2;




	private: System::Windows::Forms::ToolStripMenuItem^  m_itmHideBannerAdToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  m_sprSettingsMenuToolStripSeparator3;



	private: System::Windows::Forms::ToolStripMenuItem^  m_itmHelpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmWikiToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmTutorialToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  m_sprHelpMenuToolStripSeparator1;





	private: System::Windows::Forms::ToolStripMenuItem^  m_itmAboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  m_itmCreditsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  m_sprHelpMenuToolStripSeparator2;



	private: System::Windows::Forms::ToolStripMenuItem^  m_itmGameKillerToolStripMenuItem;

	private: System::Windows::Forms::StatusStrip^  m_sbrStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^  m_lblCounter;
	private: System::Windows::Forms::ToolStripStatusLabel^  m_lblGameKiller;
	private: System::Windows::Forms::SplitContainer^  m_splConatiner;
private: System::Windows::Forms::TabControl^  m_tbPackets;



	private: System::Windows::Forms::TabPage^  m_tbpRecv;
	private: System::Windows::Forms::ListView^  m_lstRecvList;


	private: System::Windows::Forms::ColumnHeader^  m_hdrRecvSize;
	private: System::Windows::Forms::ColumnHeader^  m_hdrRecvCode;
	private: System::Windows::Forms::Panel^  m_pnlContainer1;
private: System::Windows::Forms::ColumnHeader^  m_hdrRecvData;


	private: System::Windows::Forms::Button^  m_btnInjectRecv;
	private: System::Windows::Forms::Button^  m_btnFilterRecv;
	private: System::Windows::Forms::Button^  m_btnIgnoreRecv;
	private: System::Windows::Forms::Button^  m_btnBlockRecv;




	private: System::Windows::Forms::Label^  m_lblFilter1;
	private: System::Windows::Forms::CheckBox^  m_chxFilterEmptyRecv;


	private: System::Windows::Forms::CheckBox^  m_chxFilterNullRecv;

	private: System::Windows::Forms::Label^  m_btnGetRecvPacket;

	private: System::Windows::Forms::TextBox^  m_txtRecvPacket;

	private: System::Windows::Forms::Label^  m_lblPacket1;
	private: System::Windows::Forms::TabPage^  m_tbpSend;
	private: System::Windows::Forms::ListView^  m_lstSendList;

	private: System::Windows::Forms::ColumnHeader^  m_hdrSendSize;
private: System::Windows::Forms::ColumnHeader^  m_hdrSendCode;
private: System::Windows::Forms::ColumnHeader^  m_hdrSendData;




private: System::Windows::Forms::Panel^  m_pnlContainer2;

	private: System::Windows::Forms::Button^  m_btnInjectSend;
	private: System::Windows::Forms::Button^  m_btnFilterSend;
	private: System::Windows::Forms::Button^  m_btnIgnoreSend;
	private: System::Windows::Forms::Button^  m_btnBlockSend;
	private: System::Windows::Forms::Label^  m_lblFilter2;
	private: System::Windows::Forms::CheckBox^  m_chxFilterEmptySend;
	private: System::Windows::Forms::CheckBox^  m_chxFilterNullSend;
	private: System::Windows::Forms::Label^  m_btnGetSendPacket;
	private: System::Windows::Forms::TextBox^  m_txtSendPacket;
	private: System::Windows::Forms::Label^  m_lblPacket2;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmExecuteToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmFloodControlToolStripMenuItem;


private: System::Windows::Forms::TabPage^  m_tbpBoth;
private: System::Windows::Forms::ListView^  m_lstBothList;

private: System::Windows::Forms::ColumnHeader^  m_hdrBothSize;
private: System::Windows::Forms::ColumnHeader^  m_hdrBothCode;
private: System::Windows::Forms::ColumnHeader^  m_hdrBothData;

private: System::Windows::Forms::ToolStripMenuItem^  m_itmViewRecvToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmViewSentToolStripMenuItem;


private: System::Windows::Forms::ToolStripSeparator^  m_sprPacketsMenuToolStripSeparator1;

private: System::Windows::Forms::ContextMenuStrip^  m_ctxItemMenu;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmCreateTemplateToolStripMenuItem;
private: System::Windows::Forms::ToolStripSeparator^  m_sprItemMenuToolStripSeparator1;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmFavoriteToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmCollectToolStripMenuItem;
private: System::Windows::Forms::ToolStripSeparator^  m_sprItemMenuToolStripSeparator2;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmRemoveItemToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmClearItemsToolStripMenuItem;
private: System::Windows::Forms::ImageList^  m_lstPacketImages;
private: System::Windows::Forms::ContextMenuStrip^  m_ctxTextMenu;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmFormattedToolStripMenuItem;
private: System::Windows::Forms::ToolStripSeparator^  m_sprTextMenuToolStripSeparator1;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmInsertToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmRandomToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmByteToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmInt16ToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmInt32ToolStripMenuItem;
private: System::Windows::Forms::ToolStripSeparator^  m_sprRandomMenuToolStripSeparator1;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmAsciiToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmStringToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmValueToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmTransformToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmToInt16ToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmToInt32ToolStripMenuItem;
private: System::Windows::Forms::ToolStripSeparator^  m_sprTransformToolStripSeparator1;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmToAsciiToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmToStringToolStripMenuItem;
private: System::Windows::Forms::ToolStripSeparator^  m_sprTextMenuToolStripSeparator2;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmCutToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmCopyToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmPasteToolStripMenuItem;
private: System::Windows::Forms::ColumnHeader^  m_hdrRecvImage;
private: System::Windows::Forms::ColumnHeader^  m_hdrSendImage;
private: System::Windows::Forms::ColumnHeader^  m_hdrBothImage;
private: System::Windows::Forms::NotifyIcon^  m_ntiSystemTray;
private: System::Windows::Forms::ToolTip^  m_ttpToolTip;
private: System::Windows::Forms::Label^  m_lblBanner;
private: System::Windows::Forms::ToolStripMenuItem^  m_itmFollowItemsToolStripMenuItem;











#pragma region Windows Form Designer generated code
	private:
		System::ComponentModel::IContainer^ components;

		void InitializeComponent ( void )
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ZApplication::typeid));
			this->m_mbrStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->m_itmMapleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmMemoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprMapleMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmQuitGameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmExitGameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprMapleMenuToolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmExitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmPacketsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmViewRecvToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmViewSentToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprPacketsMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmTemplatesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmBuilderToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprPacketsMenuToolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmHistoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmPatternsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmBlockedRecvToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmIgnoredRecvToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprPatternsMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmBlockedSendToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmIgnoredSendToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprPatternsMenuToolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmCustomToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmCollectionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmFavoritesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmScriptsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmExecuteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmToolsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmFloodControlToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmSettingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmFollowItemsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprSettingsMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmAlwaysOnTopToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmTransparentToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprSettingsMenuToolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmTopLevelWindowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmSystemTrayIconToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmMinimizeOnCloseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprSettingsMenuToolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmHideBannerAdToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmHelpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmWikiToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmTutorialToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprHelpMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmAboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmCreditsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprHelpMenuToolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmGameKillerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sbrStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->m_lblCounter = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->m_lblGameKiller = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->m_splConatiner = (gcnew System::Windows::Forms::SplitContainer());
			this->m_tbPackets = (gcnew System::Windows::Forms::TabControl());
			this->m_tbpRecv = (gcnew System::Windows::Forms::TabPage());
			this->m_lstRecvList = (gcnew System::Windows::Forms::ListView());
			this->m_hdrRecvImage = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrRecvSize = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrRecvCode = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrRecvData = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_ctxItemMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->m_itmCreateTemplateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprItemMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmFavoriteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmCollectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprItemMenuToolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmRemoveItemToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmClearItemsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_pnlContainer1 = (gcnew System::Windows::Forms::Panel());
			this->m_btnInjectRecv = (gcnew System::Windows::Forms::Button());
			this->m_btnFilterRecv = (gcnew System::Windows::Forms::Button());
			this->m_btnIgnoreRecv = (gcnew System::Windows::Forms::Button());
			this->m_btnBlockRecv = (gcnew System::Windows::Forms::Button());
			this->m_lblFilter1 = (gcnew System::Windows::Forms::Label());
			this->m_chxFilterEmptyRecv = (gcnew System::Windows::Forms::CheckBox());
			this->m_chxFilterNullRecv = (gcnew System::Windows::Forms::CheckBox());
			this->m_btnGetRecvPacket = (gcnew System::Windows::Forms::Label());
			this->m_txtRecvPacket = (gcnew System::Windows::Forms::TextBox());
			this->m_ctxTextMenu = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->m_itmFormattedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprTextMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmInsertToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmRandomToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmByteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmInt16ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmInt32ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprRandomMenuToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmAsciiToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmStringToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmValueToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmTransformToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmToInt16ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmToInt32ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprTransformToolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmToAsciiToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmToStringToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_sprTextMenuToolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->m_itmCutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmCopyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_itmPasteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->m_lblPacket1 = (gcnew System::Windows::Forms::Label());
			this->m_tbpSend = (gcnew System::Windows::Forms::TabPage());
			this->m_lstSendList = (gcnew System::Windows::Forms::ListView());
			this->m_hdrSendImage = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrSendSize = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrSendCode = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrSendData = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_pnlContainer2 = (gcnew System::Windows::Forms::Panel());
			this->m_btnInjectSend = (gcnew System::Windows::Forms::Button());
			this->m_btnFilterSend = (gcnew System::Windows::Forms::Button());
			this->m_btnIgnoreSend = (gcnew System::Windows::Forms::Button());
			this->m_btnBlockSend = (gcnew System::Windows::Forms::Button());
			this->m_lblFilter2 = (gcnew System::Windows::Forms::Label());
			this->m_chxFilterEmptySend = (gcnew System::Windows::Forms::CheckBox());
			this->m_chxFilterNullSend = (gcnew System::Windows::Forms::CheckBox());
			this->m_btnGetSendPacket = (gcnew System::Windows::Forms::Label());
			this->m_txtSendPacket = (gcnew System::Windows::Forms::TextBox());
			this->m_lblPacket2 = (gcnew System::Windows::Forms::Label());
			this->m_tbpBoth = (gcnew System::Windows::Forms::TabPage());
			this->m_lstBothList = (gcnew System::Windows::Forms::ListView());
			this->m_hdrBothImage = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrBothSize = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrBothCode = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_hdrBothData = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_lstPacketImages = (gcnew System::Windows::Forms::ImageList(this->components));
			this->m_lblBanner = (gcnew System::Windows::Forms::Label());
			this->m_ntiSystemTray = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->m_ttpToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->m_mbrStrip->SuspendLayout();
			this->m_sbrStrip->SuspendLayout();
			this->m_splConatiner->Panel1->SuspendLayout();
			this->m_splConatiner->Panel2->SuspendLayout();
			this->m_splConatiner->SuspendLayout();
			this->m_tbPackets->SuspendLayout();
			this->m_tbpRecv->SuspendLayout();
			this->m_ctxItemMenu->SuspendLayout();
			this->m_pnlContainer1->SuspendLayout();
			this->m_ctxTextMenu->SuspendLayout();
			this->m_tbpSend->SuspendLayout();
			this->m_pnlContainer2->SuspendLayout();
			this->m_tbpBoth->SuspendLayout();
			this->SuspendLayout();
			// 
			// m_mbrStrip
			// 
			this->m_mbrStrip->BackColor = System::Drawing::SystemColors::Control;
			this->m_mbrStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {this->m_itmMapleToolStripMenuItem, 
				this->m_itmPacketsToolStripMenuItem, this->m_itmPatternsToolStripMenuItem, this->m_itmCollectionsToolStripMenuItem, this->m_itmScriptsToolStripMenuItem, 
				this->m_itmToolsToolStripMenuItem, this->m_itmSettingsToolStripMenuItem, this->m_itmHelpToolStripMenuItem});
			this->m_mbrStrip->Location = System::Drawing::Point(0, 0);
			this->m_mbrStrip->Name = L"m_mbrStrip";
			this->m_mbrStrip->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->m_mbrStrip->Size = System::Drawing::Size(548, 24);
			this->m_mbrStrip->TabIndex = 0;
			// 
			// m_itmMapleToolStripMenuItem
			// 
			this->m_itmMapleToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->m_itmMemoryToolStripMenuItem, 
				this->m_sprMapleMenuToolStripSeparator1, this->m_itmQuitGameToolStripMenuItem, this->m_itmExitGameToolStripMenuItem, this->m_sprMapleMenuToolStripSeparator2, 
				this->m_itmExitToolStripMenuItem});
			this->m_itmMapleToolStripMenuItem->Name = L"m_itmMapleToolStripMenuItem";
			this->m_itmMapleToolStripMenuItem->Size = System::Drawing::Size(83, 20);
			this->m_itmMapleToolStripMenuItem->Text = L"&MapleStory";
			// 
			// m_itmMemoryToolStripMenuItem
			// 
			this->m_itmMemoryToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmMemoryToolStripMenuItem.Image")));
			this->m_itmMemoryToolStripMenuItem->Name = L"m_itmMemoryToolStripMenuItem";
			this->m_itmMemoryToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->m_itmMemoryToolStripMenuItem->Text = L"Memory";
			this->m_itmMemoryToolStripMenuItem->ToolTipText = L"Manage pointers to memeory locations";
			this->m_itmMemoryToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnMemoryClick);
			// 
			// m_sprMapleMenuToolStripSeparator1
			// 
			this->m_sprMapleMenuToolStripSeparator1->Name = L"m_sprMapleMenuToolStripSeparator1";
			this->m_sprMapleMenuToolStripSeparator1->Size = System::Drawing::Size(143, 6);
			// 
			// m_itmQuitGameToolStripMenuItem
			// 
			this->m_itmQuitGameToolStripMenuItem->Name = L"m_itmQuitGameToolStripMenuItem";
			this->m_itmQuitGameToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->m_itmQuitGameToolStripMenuItem->Text = L"Quit Game";
			this->m_itmQuitGameToolStripMenuItem->ToolTipText = L"Logout of MapleStory";
			this->m_itmQuitGameToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnQuitGameClick);
			// 
			// m_itmExitGameToolStripMenuItem
			// 
			this->m_itmExitGameToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmExitGameToolStripMenuItem.Image")));
			this->m_itmExitGameToolStripMenuItem->Name = L"m_itmExitGameToolStripMenuItem";
			this->m_itmExitGameToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->m_itmExitGameToolStripMenuItem->Text = L"Exit Game";
			this->m_itmExitGameToolStripMenuItem->ToolTipText = L"Exit the MapleStory game";
			this->m_itmExitGameToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnExitGameClick);
			// 
			// m_sprMapleMenuToolStripSeparator2
			// 
			this->m_sprMapleMenuToolStripSeparator2->Name = L"m_sprMapleMenuToolStripSeparator2";
			this->m_sprMapleMenuToolStripSeparator2->Size = System::Drawing::Size(143, 6);
			// 
			// m_itmExitToolStripMenuItem
			// 
			this->m_itmExitToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmExitToolStripMenuItem.Image")));
			this->m_itmExitToolStripMenuItem->Name = L"m_itmExitToolStripMenuItem";
			this->m_itmExitToolStripMenuItem->Size = System::Drawing::Size(146, 22);
			this->m_itmExitToolStripMenuItem->Text = L"Exit";
			this->m_itmExitToolStripMenuItem->ToolTipText = L"Exit Z";
			this->m_itmExitToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnExitClick);
			// 
			// m_itmPacketsToolStripMenuItem
			// 
			this->m_itmPacketsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->m_itmViewRecvToolStripMenuItem, 
				this->m_itmViewSentToolStripMenuItem, this->m_sprPacketsMenuToolStripSeparator1, this->m_itmTemplatesToolStripMenuItem, this->m_itmBuilderToolStripMenuItem, 
				this->m_sprPacketsMenuToolStripSeparator2, this->m_itmHistoryToolStripMenuItem});
			this->m_itmPacketsToolStripMenuItem->Name = L"m_itmPacketsToolStripMenuItem";
			this->m_itmPacketsToolStripMenuItem->Size = System::Drawing::Size(63, 20);
			this->m_itmPacketsToolStripMenuItem->Text = L"&Packets";
			// 
			// m_itmViewRecvToolStripMenuItem
			// 
			this->m_itmViewRecvToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmViewRecvToolStripMenuItem.Image")));
			this->m_itmViewRecvToolStripMenuItem->Name = L"m_itmViewRecvToolStripMenuItem";
			this->m_itmViewRecvToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->m_itmViewRecvToolStripMenuItem->Text = L"Received";
			this->m_itmViewRecvToolStripMenuItem->ToolTipText = L"View received packets";
			this->m_itmViewRecvToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnViewRecvClick);
			// 
			// m_itmViewSentToolStripMenuItem
			// 
			this->m_itmViewSentToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmViewSentToolStripMenuItem.Image")));
			this->m_itmViewSentToolStripMenuItem->Name = L"m_itmViewSentToolStripMenuItem";
			this->m_itmViewSentToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->m_itmViewSentToolStripMenuItem->Text = L"Sent";
			this->m_itmViewSentToolStripMenuItem->ToolTipText = L"View sent packets";
			this->m_itmViewSentToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnViewSentClick);
			// 
			// m_sprPacketsMenuToolStripSeparator1
			// 
			this->m_sprPacketsMenuToolStripSeparator1->Name = L"m_sprPacketsMenuToolStripSeparator1";
			this->m_sprPacketsMenuToolStripSeparator1->Size = System::Drawing::Size(141, 6);
			// 
			// m_itmTemplatesToolStripMenuItem
			// 
			this->m_itmTemplatesToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmTemplatesToolStripMenuItem.Image")));
			this->m_itmTemplatesToolStripMenuItem->Name = L"m_itmTemplatesToolStripMenuItem";
			this->m_itmTemplatesToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->m_itmTemplatesToolStripMenuItem->Text = L"Templates";
			this->m_itmTemplatesToolStripMenuItem->ToolTipText = L"Manage packet templates";
			this->m_itmTemplatesToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnTemplatesClick);
			// 
			// m_itmBuilderToolStripMenuItem
			// 
			this->m_itmBuilderToolStripMenuItem->Name = L"m_itmBuilderToolStripMenuItem";
			this->m_itmBuilderToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->m_itmBuilderToolStripMenuItem->Text = L"Builder";
			this->m_itmBuilderToolStripMenuItem->ToolTipText = L"Build a packet from scratch";
			this->m_itmBuilderToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnBuilderClick);
			// 
			// m_sprPacketsMenuToolStripSeparator2
			// 
			this->m_sprPacketsMenuToolStripSeparator2->Name = L"m_sprPacketsMenuToolStripSeparator2";
			this->m_sprPacketsMenuToolStripSeparator2->Size = System::Drawing::Size(141, 6);
			// 
			// m_itmHistoryToolStripMenuItem
			// 
			this->m_itmHistoryToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmHistoryToolStripMenuItem.Image")));
			this->m_itmHistoryToolStripMenuItem->Name = L"m_itmHistoryToolStripMenuItem";
			this->m_itmHistoryToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->m_itmHistoryToolStripMenuItem->Text = L"History";
			this->m_itmHistoryToolStripMenuItem->ToolTipText = L"View all received and sent packets";
			this->m_itmHistoryToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnHistoryClick);
			// 
			// m_itmPatternsToolStripMenuItem
			// 
			this->m_itmPatternsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->m_itmBlockedRecvToolStripMenuItem, 
				this->m_itmIgnoredRecvToolStripMenuItem, this->m_sprPatternsMenuToolStripSeparator1, this->m_itmBlockedSendToolStripMenuItem, 
				this->m_itmIgnoredSendToolStripMenuItem, this->m_sprPatternsMenuToolStripSeparator2, this->m_itmCustomToolStripMenuItem});
			this->m_itmPatternsToolStripMenuItem->Name = L"m_itmPatternsToolStripMenuItem";
			this->m_itmPatternsToolStripMenuItem->Size = System::Drawing::Size(66, 20);
			this->m_itmPatternsToolStripMenuItem->Text = L"P&atterns";
			// 
			// m_itmBlockedRecvToolStripMenuItem
			// 
			this->m_itmBlockedRecvToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmBlockedRecvToolStripMenuItem.Image")));
			this->m_itmBlockedRecvToolStripMenuItem->Name = L"m_itmBlockedRecvToolStripMenuItem";
			this->m_itmBlockedRecvToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->m_itmBlockedRecvToolStripMenuItem->Text = L"Blocked (Recv)";
			this->m_itmBlockedRecvToolStripMenuItem->ToolTipText = L"Manage blocked packet patterns for received packets";
			this->m_itmBlockedRecvToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnBlockedRecvClick);
			// 
			// m_itmIgnoredRecvToolStripMenuItem
			// 
			this->m_itmIgnoredRecvToolStripMenuItem->Name = L"m_itmIgnoredRecvToolStripMenuItem";
			this->m_itmIgnoredRecvToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->m_itmIgnoredRecvToolStripMenuItem->Text = L"Ignored (Recv)";
			this->m_itmIgnoredRecvToolStripMenuItem->ToolTipText = L"Manage ignored packet patterns for received packets";
			this->m_itmIgnoredRecvToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnIgnoredRecvClick);
			// 
			// m_sprPatternsMenuToolStripSeparator1
			// 
			this->m_sprPatternsMenuToolStripSeparator1->Name = L"m_sprPatternsMenuToolStripSeparator1";
			this->m_sprPatternsMenuToolStripSeparator1->Size = System::Drawing::Size(170, 6);
			// 
			// m_itmBlockedSendToolStripMenuItem
			// 
			this->m_itmBlockedSendToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmBlockedSendToolStripMenuItem.Image")));
			this->m_itmBlockedSendToolStripMenuItem->Name = L"m_itmBlockedSendToolStripMenuItem";
			this->m_itmBlockedSendToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->m_itmBlockedSendToolStripMenuItem->Text = L"Blocked (Send)";
			this->m_itmBlockedSendToolStripMenuItem->ToolTipText = L"Manage blocked packet patterns for sent packets";
			this->m_itmBlockedSendToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnBlockedSendClick);
			// 
			// m_itmIgnoredSendToolStripMenuItem
			// 
			this->m_itmIgnoredSendToolStripMenuItem->Name = L"m_itmIgnoredSendToolStripMenuItem";
			this->m_itmIgnoredSendToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->m_itmIgnoredSendToolStripMenuItem->Text = L"Ignored (Send)";
			this->m_itmIgnoredSendToolStripMenuItem->ToolTipText = L"Manage ignored packet patterns for sent packets";
			this->m_itmIgnoredSendToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnIgnoredSendClick);
			// 
			// m_sprPatternsMenuToolStripSeparator2
			// 
			this->m_sprPatternsMenuToolStripSeparator2->Name = L"m_sprPatternsMenuToolStripSeparator2";
			this->m_sprPatternsMenuToolStripSeparator2->Size = System::Drawing::Size(170, 6);
			// 
			// m_itmCustomToolStripMenuItem
			// 
			this->m_itmCustomToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmCustomToolStripMenuItem.Image")));
			this->m_itmCustomToolStripMenuItem->Name = L"m_itmCustomToolStripMenuItem";
			this->m_itmCustomToolStripMenuItem->Size = System::Drawing::Size(173, 22);
			this->m_itmCustomToolStripMenuItem->Text = L"Custom";
			this->m_itmCustomToolStripMenuItem->ToolTipText = L"Commonly used patterns";
			this->m_itmCustomToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnCustomClick);
			// 
			// m_itmCollectionsToolStripMenuItem
			// 
			this->m_itmCollectionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->m_itmFavoritesToolStripMenuItem});
			this->m_itmCollectionsToolStripMenuItem->Name = L"m_itmCollectionsToolStripMenuItem";
			this->m_itmCollectionsToolStripMenuItem->Size = System::Drawing::Size(81, 20);
			this->m_itmCollectionsToolStripMenuItem->Text = L"&Collections";
			this->m_itmCollectionsToolStripMenuItem->DropDownItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &ZApplication::OnCollectionsDropDrownItemClicked);
			// 
			// m_itmFavoritesToolStripMenuItem
			// 
			this->m_itmFavoritesToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmFavoritesToolStripMenuItem.Image")));
			this->m_itmFavoritesToolStripMenuItem->Name = L"m_itmFavoritesToolStripMenuItem";
			this->m_itmFavoritesToolStripMenuItem->Size = System::Drawing::Size(137, 22);
			this->m_itmFavoritesToolStripMenuItem->Text = L"Favorites";
			this->m_itmFavoritesToolStripMenuItem->ToolTipText = L"Packets marked as favorite";
			// 
			// m_itmScriptsToolStripMenuItem
			// 
			this->m_itmScriptsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->m_itmExecuteToolStripMenuItem});
			this->m_itmScriptsToolStripMenuItem->Name = L"m_itmScriptsToolStripMenuItem";
			this->m_itmScriptsToolStripMenuItem->Size = System::Drawing::Size(58, 20);
			this->m_itmScriptsToolStripMenuItem->Text = L"Sc&ripts";
			// 
			// m_itmExecuteToolStripMenuItem
			// 
			this->m_itmExecuteToolStripMenuItem->Enabled = false;
			this->m_itmExecuteToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmExecuteToolStripMenuItem.Image")));
			this->m_itmExecuteToolStripMenuItem->Name = L"m_itmExecuteToolStripMenuItem";
			this->m_itmExecuteToolStripMenuItem->Size = System::Drawing::Size(130, 22);
			this->m_itmExecuteToolStripMenuItem->Text = L"Execute";
			this->m_itmExecuteToolStripMenuItem->ToolTipText = L"Execute a Z script";
			this->m_itmExecuteToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnExecuteClick);
			// 
			// m_itmToolsToolStripMenuItem
			// 
			this->m_itmToolsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->m_itmFloodControlToolStripMenuItem});
			this->m_itmToolsToolStripMenuItem->Name = L"m_itmToolsToolStripMenuItem";
			this->m_itmToolsToolStripMenuItem->Size = System::Drawing::Size(49, 20);
			this->m_itmToolsToolStripMenuItem->Text = L"&Tools";
			// 
			// m_itmFloodControlToolStripMenuItem
			// 
			this->m_itmFloodControlToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmFloodControlToolStripMenuItem.Image")));
			this->m_itmFloodControlToolStripMenuItem->Name = L"m_itmFloodControlToolStripMenuItem";
			this->m_itmFloodControlToolStripMenuItem->Size = System::Drawing::Size(161, 22);
			this->m_itmFloodControlToolStripMenuItem->Text = L"Flood Control";
			this->m_itmFloodControlToolStripMenuItem->ToolTipText = L"Create or prevent packet floods";
			this->m_itmFloodControlToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnFloodControlClick);
			// 
			// m_itmSettingsToolStripMenuItem
			// 
			this->m_itmSettingsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {this->m_itmFollowItemsToolStripMenuItem, 
				this->m_sprSettingsMenuToolStripSeparator1, this->m_itmAlwaysOnTopToolStripMenuItem, this->m_itmTransparentToolStripMenuItem, 
				this->m_sprSettingsMenuToolStripSeparator2, this->m_itmTopLevelWindowToolStripMenuItem, this->m_itmSystemTrayIconToolStripMenuItem, 
				this->m_itmMinimizeOnCloseToolStripMenuItem, this->m_sprSettingsMenuToolStripSeparator3, this->m_itmHideBannerAdToolStripMenuItem});
			this->m_itmSettingsToolStripMenuItem->Name = L"m_itmSettingsToolStripMenuItem";
			this->m_itmSettingsToolStripMenuItem->Size = System::Drawing::Size(65, 20);
			this->m_itmSettingsToolStripMenuItem->Text = L"&Settings";
			// 
			// m_itmFollowItemsToolStripMenuItem
			// 
			this->m_itmFollowItemsToolStripMenuItem->Checked = true;
			this->m_itmFollowItemsToolStripMenuItem->CheckOnClick = true;
			this->m_itmFollowItemsToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->m_itmFollowItemsToolStripMenuItem->Name = L"m_itmFollowItemsToolStripMenuItem";
			this->m_itmFollowItemsToolStripMenuItem->Size = System::Drawing::Size(227, 22);
			this->m_itmFollowItemsToolStripMenuItem->Text = L"Follow Items In List View";
			// 
			// m_sprSettingsMenuToolStripSeparator1
			// 
			this->m_sprSettingsMenuToolStripSeparator1->Name = L"m_sprSettingsMenuToolStripSeparator1";
			this->m_sprSettingsMenuToolStripSeparator1->Size = System::Drawing::Size(224, 6);
			// 
			// m_itmAlwaysOnTopToolStripMenuItem
			// 
			this->m_itmAlwaysOnTopToolStripMenuItem->Checked = true;
			this->m_itmAlwaysOnTopToolStripMenuItem->CheckOnClick = true;
			this->m_itmAlwaysOnTopToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->m_itmAlwaysOnTopToolStripMenuItem->Name = L"m_itmAlwaysOnTopToolStripMenuItem";
			this->m_itmAlwaysOnTopToolStripMenuItem->Size = System::Drawing::Size(227, 22);
			this->m_itmAlwaysOnTopToolStripMenuItem->Text = L"Always On Top";
			this->m_itmAlwaysOnTopToolStripMenuItem->ToolTipText = L"Display Z windows on top of all others";
			this->m_itmAlwaysOnTopToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnAlwaysOnTopClick);
			// 
			// m_itmTransparentToolStripMenuItem
			// 
			this->m_itmTransparentToolStripMenuItem->CheckOnClick = true;
			this->m_itmTransparentToolStripMenuItem->Name = L"m_itmTransparentToolStripMenuItem";
			this->m_itmTransparentToolStripMenuItem->Size = System::Drawing::Size(227, 22);
			this->m_itmTransparentToolStripMenuItem->Text = L"Transparent";
			this->m_itmTransparentToolStripMenuItem->ToolTipText = L"Enable or disable transparency";
			this->m_itmTransparentToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnTransparentClick);
			// 
			// m_sprSettingsMenuToolStripSeparator2
			// 
			this->m_sprSettingsMenuToolStripSeparator2->Name = L"m_sprSettingsMenuToolStripSeparator2";
			this->m_sprSettingsMenuToolStripSeparator2->Size = System::Drawing::Size(224, 6);
			// 
			// m_itmTopLevelWindowToolStripMenuItem
			// 
			this->m_itmTopLevelWindowToolStripMenuItem->Checked = true;
			this->m_itmTopLevelWindowToolStripMenuItem->CheckOnClick = true;
			this->m_itmTopLevelWindowToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->m_itmTopLevelWindowToolStripMenuItem->Name = L"m_itmTopLevelWindowToolStripMenuItem";
			this->m_itmTopLevelWindowToolStripMenuItem->Size = System::Drawing::Size(227, 22);
			this->m_itmTopLevelWindowToolStripMenuItem->Text = L"Show In Taskbar";
			this->m_itmTopLevelWindowToolStripMenuItem->ToolTipText = L"Display Z in the system taskbar";
			this->m_itmTopLevelWindowToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnTopLevelWindowClick);
			// 
			// m_itmSystemTrayIconToolStripMenuItem
			// 
			this->m_itmSystemTrayIconToolStripMenuItem->CheckOnClick = true;
			this->m_itmSystemTrayIconToolStripMenuItem->Name = L"m_itmSystemTrayIconToolStripMenuItem";
			this->m_itmSystemTrayIconToolStripMenuItem->Size = System::Drawing::Size(227, 22);
			this->m_itmSystemTrayIconToolStripMenuItem->Text = L"System Tray Icon";
			this->m_itmSystemTrayIconToolStripMenuItem->ToolTipText = L"Display Z in the system tray";
			this->m_itmSystemTrayIconToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnSystemTrayIconClick);
			// 
			// m_itmMinimizeOnCloseToolStripMenuItem
			// 
			this->m_itmMinimizeOnCloseToolStripMenuItem->CheckOnClick = true;
			this->m_itmMinimizeOnCloseToolStripMenuItem->Name = L"m_itmMinimizeOnCloseToolStripMenuItem";
			this->m_itmMinimizeOnCloseToolStripMenuItem->Size = System::Drawing::Size(227, 22);
			this->m_itmMinimizeOnCloseToolStripMenuItem->Text = L"Minimize On Close";
			this->m_itmMinimizeOnCloseToolStripMenuItem->ToolTipText = L"Minimize Z when the window is closed";
			this->m_itmMinimizeOnCloseToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnMinimizeOnCloseClick);
			// 
			// m_sprSettingsMenuToolStripSeparator3
			// 
			this->m_sprSettingsMenuToolStripSeparator3->Name = L"m_sprSettingsMenuToolStripSeparator3";
			this->m_sprSettingsMenuToolStripSeparator3->Size = System::Drawing::Size(224, 6);
			// 
			// m_itmHideBannerAdToolStripMenuItem
			// 
			this->m_itmHideBannerAdToolStripMenuItem->CheckOnClick = true;
			this->m_itmHideBannerAdToolStripMenuItem->Name = L"m_itmHideBannerAdToolStripMenuItem";
			this->m_itmHideBannerAdToolStripMenuItem->Size = System::Drawing::Size(227, 22);
			this->m_itmHideBannerAdToolStripMenuItem->Text = L"Hide Banner Ad";
			this->m_itmHideBannerAdToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnHideBannerAdClick);
			// 
			// m_itmHelpToolStripMenuItem
			// 
			this->m_itmHelpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->m_itmWikiToolStripMenuItem, 
				this->m_itmTutorialToolStripMenuItem, this->m_sprHelpMenuToolStripSeparator1, this->m_itmAboutToolStripMenuItem, this->m_itmCreditsToolStripMenuItem, 
				this->m_sprHelpMenuToolStripSeparator2, this->m_itmGameKillerToolStripMenuItem});
			this->m_itmHelpToolStripMenuItem->Name = L"m_itmHelpToolStripMenuItem";
			this->m_itmHelpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
			this->m_itmHelpToolStripMenuItem->Text = L"&Help";
			this->m_itmHelpToolStripMenuItem->DropDownItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &ZApplication::OnHelpDropDownItemClicked);
			// 
			// m_itmWikiToolStripMenuItem
			// 
			this->m_itmWikiToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmWikiToolStripMenuItem.Image")));
			this->m_itmWikiToolStripMenuItem->Name = L"m_itmWikiToolStripMenuItem";
			this->m_itmWikiToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->m_itmWikiToolStripMenuItem->Text = L"Wiki";
			this->m_itmWikiToolStripMenuItem->ToolTipText = L"View the Z wiki";
			// 
			// m_itmTutorialToolStripMenuItem
			// 
			this->m_itmTutorialToolStripMenuItem->Name = L"m_itmTutorialToolStripMenuItem";
			this->m_itmTutorialToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->m_itmTutorialToolStripMenuItem->Text = L"Tutorial";
			this->m_itmTutorialToolStripMenuItem->ToolTipText = L"View the Z tutorial";
			// 
			// m_sprHelpMenuToolStripSeparator1
			// 
			this->m_sprHelpMenuToolStripSeparator1->Name = L"m_sprHelpMenuToolStripSeparator1";
			this->m_sprHelpMenuToolStripSeparator1->Size = System::Drawing::Size(145, 6);
			// 
			// m_itmAboutToolStripMenuItem
			// 
			this->m_itmAboutToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmAboutToolStripMenuItem.Image")));
			this->m_itmAboutToolStripMenuItem->Name = L"m_itmAboutToolStripMenuItem";
			this->m_itmAboutToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->m_itmAboutToolStripMenuItem->Text = L"About";
			this->m_itmAboutToolStripMenuItem->ToolTipText = L"About Z";
			// 
			// m_itmCreditsToolStripMenuItem
			// 
			this->m_itmCreditsToolStripMenuItem->Name = L"m_itmCreditsToolStripMenuItem";
			this->m_itmCreditsToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->m_itmCreditsToolStripMenuItem->Text = L"Credits";
			// 
			// m_sprHelpMenuToolStripSeparator2
			// 
			this->m_sprHelpMenuToolStripSeparator2->Name = L"m_sprHelpMenuToolStripSeparator2";
			this->m_sprHelpMenuToolStripSeparator2->Size = System::Drawing::Size(145, 6);
			// 
			// m_itmGameKillerToolStripMenuItem
			// 
			this->m_itmGameKillerToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmGameKillerToolStripMenuItem.Image")));
			this->m_itmGameKillerToolStripMenuItem->Name = L"m_itmGameKillerToolStripMenuItem";
			this->m_itmGameKillerToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->m_itmGameKillerToolStripMenuItem->Text = L"GameKiller";
			this->m_itmGameKillerToolStripMenuItem->ToolTipText = L"Visit the GameKiller.net website";
			// 
			// m_sbrStrip
			// 
			this->m_sbrStrip->AutoSize = false;
			this->m_sbrStrip->BackColor = System::Drawing::SystemColors::Control;
			this->m_sbrStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->m_lblCounter, this->m_lblGameKiller});
			this->m_sbrStrip->Location = System::Drawing::Point(0, 523);
			this->m_sbrStrip->Name = L"m_sbrStrip";
			this->m_sbrStrip->ShowItemToolTips = true;
			this->m_sbrStrip->Size = System::Drawing::Size(548, 25);
			this->m_sbrStrip->SizingGrip = false;
			this->m_sbrStrip->TabIndex = 1;
			// 
			// m_lblCounter
			// 
			this->m_lblCounter->Name = L"m_lblCounter";
			this->m_lblCounter->Size = System::Drawing::Size(394, 20);
			this->m_lblCounter->Spring = true;
			this->m_lblCounter->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// m_lblGameKiller
			// 
			this->m_lblGameKiller->ForeColor = System::Drawing::Color::DimGray;
			this->m_lblGameKiller->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_lblGameKiller.Image")));
			this->m_lblGameKiller->Name = L"m_lblGameKiller";
			this->m_lblGameKiller->Size = System::Drawing::Size(139, 20);
			this->m_lblGameKiller->Text = L"www.GameKiller.net";
			// 
			// m_splConatiner
			// 
			this->m_splConatiner->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_splConatiner->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->m_splConatiner->IsSplitterFixed = true;
			this->m_splConatiner->Location = System::Drawing::Point(0, 24);
			this->m_splConatiner->Margin = System::Windows::Forms::Padding(0);
			this->m_splConatiner->Name = L"m_splConatiner";
			this->m_splConatiner->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// m_splConatiner.Panel1
			// 
			this->m_splConatiner->Panel1->Controls->Add(this->m_tbPackets);
			this->m_splConatiner->Panel1->Padding = System::Windows::Forms::Padding(4, 4, 4, 2);
			// 
			// m_splConatiner.Panel2
			// 
			this->m_splConatiner->Panel2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_splConatiner.Panel2.BackgroundImage")));
			this->m_splConatiner->Panel2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->m_splConatiner->Panel2->Controls->Add(this->m_lblBanner);
			this->m_splConatiner->Size = System::Drawing::Size(548, 499);
			this->m_splConatiner->SplitterDistance = 445;
			this->m_splConatiner->SplitterWidth = 1;
			this->m_splConatiner->TabIndex = 0;
			this->m_splConatiner->TabStop = false;
			// 
			// m_tbPackets
			// 
			this->m_tbPackets->Controls->Add(this->m_tbpRecv);
			this->m_tbPackets->Controls->Add(this->m_tbpSend);
			this->m_tbPackets->Controls->Add(this->m_tbpBoth);
			this->m_tbPackets->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_tbPackets->HotTrack = true;
			this->m_tbPackets->ImageList = this->m_lstPacketImages;
			this->m_tbPackets->ItemSize = System::Drawing::Size(80, 18);
			this->m_tbPackets->Location = System::Drawing::Point(4, 4);
			this->m_tbPackets->Margin = System::Windows::Forms::Padding(0);
			this->m_tbPackets->Multiline = true;
			this->m_tbPackets->Name = L"m_tbPackets";
			this->m_tbPackets->Padding = System::Drawing::Point(8, 4);
			this->m_tbPackets->SelectedIndex = 0;
			this->m_tbPackets->ShowToolTips = true;
			this->m_tbPackets->Size = System::Drawing::Size(540, 439);
			this->m_tbPackets->TabIndex = 1;
			// 
			// m_tbpRecv
			// 
			this->m_tbpRecv->BackColor = System::Drawing::Color::White;
			this->m_tbpRecv->Controls->Add(this->m_lstRecvList);
			this->m_tbpRecv->Controls->Add(this->m_pnlContainer1);
			this->m_tbpRecv->ImageIndex = 0;
			this->m_tbpRecv->Location = System::Drawing::Point(4, 22);
			this->m_tbpRecv->Margin = System::Windows::Forms::Padding(1);
			this->m_tbpRecv->Name = L"m_tbpRecv";
			this->m_tbpRecv->Padding = System::Windows::Forms::Padding(3, 3, 3, 1);
			this->m_tbpRecv->Size = System::Drawing::Size(532, 413);
			this->m_tbpRecv->TabIndex = 0;
			this->m_tbpRecv->Text = L"Received";
			this->m_tbpRecv->ToolTipText = L"View all packets received from the server";
			// 
			// m_lstRecvList
			// 
			this->m_lstRecvList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->m_hdrRecvImage, 
				this->m_hdrRecvSize, this->m_hdrRecvCode, this->m_hdrRecvData});
			this->m_lstRecvList->ContextMenuStrip = this->m_ctxItemMenu;
			this->m_lstRecvList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_lstRecvList->FullRowSelect = true;
			this->m_lstRecvList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->m_lstRecvList->Location = System::Drawing::Point(3, 3);
			this->m_lstRecvList->Margin = System::Windows::Forms::Padding(0);
			this->m_lstRecvList->Name = L"m_lstRecvList";
			this->m_lstRecvList->Size = System::Drawing::Size(526, 351);
			this->m_lstRecvList->TabIndex = 1;
			this->m_lstRecvList->UseCompatibleStateImageBehavior = false;
			this->m_lstRecvList->View = System::Windows::Forms::View::Details;
			this->m_lstRecvList->ItemMouseHover += gcnew System::Windows::Forms::ListViewItemMouseHoverEventHandler(this, &ZApplication::OnListItemMouseHover);
			this->m_lstRecvList->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &ZApplication::OnRecvListItemSelectionChanged);
			this->m_lstRecvList->ColumnWidthChanging += gcnew System::Windows::Forms::ColumnWidthChangingEventHandler(this, &ZApplication::OnListColumnWidthChanging);
			// 
			// m_hdrRecvImage
			// 
			this->m_hdrRecvImage->Text = L"";
			this->m_hdrRecvImage->Width = 0;
			// 
			// m_hdrRecvSize
			// 
			this->m_hdrRecvSize->Text = L"Size";
			this->m_hdrRecvSize->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrRecvSize->Width = 45;
			// 
			// m_hdrRecvCode
			// 
			this->m_hdrRecvCode->Text = L"Code";
			this->m_hdrRecvCode->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrRecvCode->Width = 65;
			// 
			// m_hdrRecvData
			// 
			this->m_hdrRecvData->Text = L"Data";
			this->m_hdrRecvData->Width = 395;
			// 
			// m_ctxItemMenu
			// 
			this->m_ctxItemMenu->BackColor = System::Drawing::SystemColors::Menu;
			this->m_ctxItemMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->m_itmCreateTemplateToolStripMenuItem, 
				this->m_sprItemMenuToolStripSeparator1, this->m_itmFavoriteToolStripMenuItem, this->m_itmCollectToolStripMenuItem, this->m_sprItemMenuToolStripSeparator2, 
				this->m_itmRemoveItemToolStripMenuItem, this->m_itmClearItemsToolStripMenuItem});
			this->m_ctxItemMenu->Name = L"m_ctxItemMenu";
			this->m_ctxItemMenu->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->m_ctxItemMenu->Size = System::Drawing::Size(182, 126);
			this->m_ctxItemMenu->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &ZApplication::OnItemMenuOpening);
			// 
			// m_itmCreateTemplateToolStripMenuItem
			// 
			this->m_itmCreateTemplateToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmCreateTemplateToolStripMenuItem.Image")));
			this->m_itmCreateTemplateToolStripMenuItem->Name = L"m_itmCreateTemplateToolStripMenuItem";
			this->m_itmCreateTemplateToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->m_itmCreateTemplateToolStripMenuItem->Text = L"Create Template";
			this->m_itmCreateTemplateToolStripMenuItem->ToolTipText = L"Create a template to match this packet";
			this->m_itmCreateTemplateToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnCreateTemplateClick);
			// 
			// m_sprItemMenuToolStripSeparator1
			// 
			this->m_sprItemMenuToolStripSeparator1->Name = L"m_sprItemMenuToolStripSeparator1";
			this->m_sprItemMenuToolStripSeparator1->Size = System::Drawing::Size(178, 6);
			// 
			// m_itmFavoriteToolStripMenuItem
			// 
			this->m_itmFavoriteToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmFavoriteToolStripMenuItem.Image")));
			this->m_itmFavoriteToolStripMenuItem->Name = L"m_itmFavoriteToolStripMenuItem";
			this->m_itmFavoriteToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->m_itmFavoriteToolStripMenuItem->Text = L"Favorite";
			this->m_itmFavoriteToolStripMenuItem->ToolTipText = L"Add this packet to your Favorites";
			this->m_itmFavoriteToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnAppendFavoritesClick);
			// 
			// m_itmCollectToolStripMenuItem
			// 
			this->m_itmCollectToolStripMenuItem->Name = L"m_itmCollectToolStripMenuItem";
			this->m_itmCollectToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->m_itmCollectToolStripMenuItem->Text = L"Collect";
			this->m_itmCollectToolStripMenuItem->DropDownItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &ZApplication::OnCollectDropDownItemClicked);
			// 
			// m_sprItemMenuToolStripSeparator2
			// 
			this->m_sprItemMenuToolStripSeparator2->Name = L"m_sprItemMenuToolStripSeparator2";
			this->m_sprItemMenuToolStripSeparator2->Size = System::Drawing::Size(178, 6);
			// 
			// m_itmRemoveItemToolStripMenuItem
			// 
			this->m_itmRemoveItemToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmRemoveItemToolStripMenuItem.Image")));
			this->m_itmRemoveItemToolStripMenuItem->Name = L"m_itmRemoveItemToolStripMenuItem";
			this->m_itmRemoveItemToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->m_itmRemoveItemToolStripMenuItem->Text = L"Remove";
			this->m_itmRemoveItemToolStripMenuItem->ToolTipText = L"Remove this packet from the list";
			this->m_itmRemoveItemToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnRemoveItemClick);
			// 
			// m_itmClearItemsToolStripMenuItem
			// 
			this->m_itmClearItemsToolStripMenuItem->Name = L"m_itmClearItemsToolStripMenuItem";
			this->m_itmClearItemsToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->m_itmClearItemsToolStripMenuItem->Text = L"Clear All";
			this->m_itmClearItemsToolStripMenuItem->ToolTipText = L"Remove all packets from the list";
			this->m_itmClearItemsToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnClearItemsClick);
			// 
			// m_pnlContainer1
			// 
			this->m_pnlContainer1->Controls->Add(this->m_btnInjectRecv);
			this->m_pnlContainer1->Controls->Add(this->m_btnFilterRecv);
			this->m_pnlContainer1->Controls->Add(this->m_btnIgnoreRecv);
			this->m_pnlContainer1->Controls->Add(this->m_btnBlockRecv);
			this->m_pnlContainer1->Controls->Add(this->m_lblFilter1);
			this->m_pnlContainer1->Controls->Add(this->m_chxFilterEmptyRecv);
			this->m_pnlContainer1->Controls->Add(this->m_chxFilterNullRecv);
			this->m_pnlContainer1->Controls->Add(this->m_btnGetRecvPacket);
			this->m_pnlContainer1->Controls->Add(this->m_txtRecvPacket);
			this->m_pnlContainer1->Controls->Add(this->m_lblPacket1);
			this->m_pnlContainer1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->m_pnlContainer1->Location = System::Drawing::Point(3, 354);
			this->m_pnlContainer1->Margin = System::Windows::Forms::Padding(0);
			this->m_pnlContainer1->Name = L"m_pnlContainer1";
			this->m_pnlContainer1->Padding = System::Windows::Forms::Padding(2);
			this->m_pnlContainer1->Size = System::Drawing::Size(526, 58);
			this->m_pnlContainer1->TabIndex = 0;
			// 
			// m_btnInjectRecv
			// 
			this->m_btnInjectRecv->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnInjectRecv->Enabled = false;
			this->m_btnInjectRecv->Location = System::Drawing::Point(263, 30);
			this->m_btnInjectRecv->Margin = System::Windows::Forms::Padding(0);
			this->m_btnInjectRecv->Name = L"m_btnInjectRecv";
			this->m_btnInjectRecv->Size = System::Drawing::Size(65, 25);
			this->m_btnInjectRecv->TabIndex = 3;
			this->m_btnInjectRecv->TabStop = false;
			this->m_btnInjectRecv->Text = L"Inject";
			this->m_ttpToolTip->SetToolTip(this->m_btnInjectRecv, L"Inject a packet into the received packets stream");
			this->m_btnInjectRecv->UseVisualStyleBackColor = true;
			this->m_btnInjectRecv->Click += gcnew System::EventHandler(this, &ZApplication::OnInjectRecvClick);
			// 
			// m_btnFilterRecv
			// 
			this->m_btnFilterRecv->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnFilterRecv->Enabled = false;
			this->m_btnFilterRecv->Location = System::Drawing::Point(328, 30);
			this->m_btnFilterRecv->Margin = System::Windows::Forms::Padding(0);
			this->m_btnFilterRecv->Name = L"m_btnFilterRecv";
			this->m_btnFilterRecv->Size = System::Drawing::Size(65, 25);
			this->m_btnFilterRecv->TabIndex = 4;
			this->m_btnFilterRecv->Text = L"Filter";
			this->m_ttpToolTip->SetToolTip(this->m_btnFilterRecv, L"Search through the packets for specific data");
			this->m_btnFilterRecv->UseVisualStyleBackColor = true;
			this->m_btnFilterRecv->Click += gcnew System::EventHandler(this, &ZApplication::OnFilterRecvClick);
			// 
			// m_btnIgnoreRecv
			// 
			this->m_btnIgnoreRecv->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnIgnoreRecv->Enabled = false;
			this->m_btnIgnoreRecv->Location = System::Drawing::Point(393, 30);
			this->m_btnIgnoreRecv->Margin = System::Windows::Forms::Padding(0);
			this->m_btnIgnoreRecv->Name = L"m_btnIgnoreRecv";
			this->m_btnIgnoreRecv->Size = System::Drawing::Size(65, 25);
			this->m_btnIgnoreRecv->TabIndex = 5;
			this->m_btnIgnoreRecv->Text = L"Ignore";
			this->m_ttpToolTip->SetToolTip(this->m_btnIgnoreRecv, L"Add a specific packet or pattern to the ignore list");
			this->m_btnIgnoreRecv->UseVisualStyleBackColor = true;
			this->m_btnIgnoreRecv->Click += gcnew System::EventHandler(this, &ZApplication::OnIgnoreRecvClick);
			// 
			// m_btnBlockRecv
			// 
			this->m_btnBlockRecv->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnBlockRecv->Enabled = false;
			this->m_btnBlockRecv->Location = System::Drawing::Point(458, 30);
			this->m_btnBlockRecv->Margin = System::Windows::Forms::Padding(0);
			this->m_btnBlockRecv->Name = L"m_btnBlockRecv";
			this->m_btnBlockRecv->Size = System::Drawing::Size(65, 25);
			this->m_btnBlockRecv->TabIndex = 6;
			this->m_btnBlockRecv->Text = L"Block";
			this->m_ttpToolTip->SetToolTip(this->m_btnBlockRecv, L"Add a specific packet or pattern to the blocked list");
			this->m_btnBlockRecv->UseVisualStyleBackColor = true;
			this->m_btnBlockRecv->Click += gcnew System::EventHandler(this, &ZApplication::OnBlockRecvClick);
			// 
			// m_lblFilter1
			// 
			this->m_lblFilter1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_lblFilter1.Image")));
			this->m_lblFilter1->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->m_lblFilter1->Location = System::Drawing::Point(5, 30);
			this->m_lblFilter1->Margin = System::Windows::Forms::Padding(0);
			this->m_lblFilter1->Name = L"m_lblFilter1";
			this->m_lblFilter1->Size = System::Drawing::Size(56, 25);
			this->m_lblFilter1->TabIndex = 3;
			this->m_lblFilter1->Text = L"Filter";
			this->m_lblFilter1->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// m_chxFilterEmptyRecv
			// 
			this->m_chxFilterEmptyRecv->Location = System::Drawing::Point(150, 30);
			this->m_chxFilterEmptyRecv->Margin = System::Windows::Forms::Padding(0);
			this->m_chxFilterEmptyRecv->Name = L"m_chxFilterEmptyRecv";
			this->m_chxFilterEmptyRecv->Padding = System::Windows::Forms::Padding(4, 0, 0, 0);
			this->m_chxFilterEmptyRecv->Size = System::Drawing::Size(95, 25);
			this->m_chxFilterEmptyRecv->TabIndex = 0;
			this->m_chxFilterEmptyRecv->TabStop = false;
			this->m_chxFilterEmptyRecv->Text = L"Empty data";
			this->m_ttpToolTip->SetToolTip(this->m_chxFilterEmptyRecv, L"Filter out packets that contain no data");
			this->m_chxFilterEmptyRecv->UseVisualStyleBackColor = true;
			this->m_chxFilterEmptyRecv->CheckedChanged += gcnew System::EventHandler(this, &ZApplication::OnFilterEmptyRecvCheckedChanged);
			// 
			// m_chxFilterNullRecv
			// 
			this->m_chxFilterNullRecv->Location = System::Drawing::Point(65, 30);
			this->m_chxFilterNullRecv->Margin = System::Windows::Forms::Padding(0);
			this->m_chxFilterNullRecv->Name = L"m_chxFilterNullRecv";
			this->m_chxFilterNullRecv->Padding = System::Windows::Forms::Padding(4, 0, 0, 0);
			this->m_chxFilterNullRecv->Size = System::Drawing::Size(80, 25);
			this->m_chxFilterNullRecv->TabIndex = 0;
			this->m_chxFilterNullRecv->TabStop = false;
			this->m_chxFilterNullRecv->Text = L"Null data";
			this->m_ttpToolTip->SetToolTip(this->m_chxFilterNullRecv, L"Filter out packets that contain only NULL data");
			this->m_chxFilterNullRecv->UseVisualStyleBackColor = true;
			this->m_chxFilterNullRecv->CheckedChanged += gcnew System::EventHandler(this, &ZApplication::OnFilterNullRecvCheckedChanged);
			// 
			// m_btnGetRecvPacket
			// 
			this->m_btnGetRecvPacket->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnGetRecvPacket->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->m_btnGetRecvPacket->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_btnGetRecvPacket.Image")));
			this->m_btnGetRecvPacket->Location = System::Drawing::Point(493, 5);
			this->m_btnGetRecvPacket->Margin = System::Windows::Forms::Padding(0);
			this->m_btnGetRecvPacket->Name = L"m_btnGetRecvPacket";
			this->m_btnGetRecvPacket->Size = System::Drawing::Size(30, 21);
			this->m_btnGetRecvPacket->TabIndex = 0;
			this->m_btnGetRecvPacket->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->m_btnGetRecvPacket->Click += gcnew System::EventHandler(this, &ZApplication::OnGetRecvPacketClick);
			// 
			// m_txtRecvPacket
			// 
			this->m_txtRecvPacket->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_txtRecvPacket->ContextMenuStrip = this->m_ctxTextMenu;
			this->m_txtRecvPacket->Location = System::Drawing::Point(60, 5);
			this->m_txtRecvPacket->Margin = System::Windows::Forms::Padding(0);
			this->m_txtRecvPacket->MaxLength = 0;
			this->m_txtRecvPacket->Name = L"m_txtRecvPacket";
			this->m_txtRecvPacket->Size = System::Drawing::Size(433, 21);
			this->m_txtRecvPacket->TabIndex = 2;
			this->m_txtRecvPacket->TextChanged += gcnew System::EventHandler(this, &ZApplication::OnPacketTextChanged);
			this->m_txtRecvPacket->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &ZApplication::OnRecvPacketMouseDoubleClick);
			this->m_txtRecvPacket->Enter += gcnew System::EventHandler(this, &ZApplication::OnRecvPacketEnter);
			// 
			// m_ctxTextMenu
			// 
			this->m_ctxTextMenu->BackColor = System::Drawing::SystemColors::Menu;
			this->m_ctxTextMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(8) {this->m_itmFormattedToolStripMenuItem, 
				this->m_sprTextMenuToolStripSeparator1, this->m_itmInsertToolStripMenuItem, this->m_itmTransformToolStripMenuItem, this->m_sprTextMenuToolStripSeparator2, 
				this->m_itmCutToolStripMenuItem, this->m_itmCopyToolStripMenuItem, this->m_itmPasteToolStripMenuItem});
			this->m_ctxTextMenu->Name = L"m_ctxTextMenu";
			this->m_ctxTextMenu->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->m_ctxTextMenu->Size = System::Drawing::Size(145, 148);
			this->m_ctxTextMenu->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &ZApplication::OnTextMenuOpening);
			// 
			// m_itmFormattedToolStripMenuItem
			// 
			this->m_itmFormattedToolStripMenuItem->Checked = true;
			this->m_itmFormattedToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->m_itmFormattedToolStripMenuItem->Enabled = false;
			this->m_itmFormattedToolStripMenuItem->Name = L"m_itmFormattedToolStripMenuItem";
			this->m_itmFormattedToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->m_itmFormattedToolStripMenuItem->Text = L"Formatted";
			this->m_itmFormattedToolStripMenuItem->ToolTipText = L"View the packet byte code with strings parsed";
			this->m_itmFormattedToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnTextFormatClick);
			// 
			// m_sprTextMenuToolStripSeparator1
			// 
			this->m_sprTextMenuToolStripSeparator1->Name = L"m_sprTextMenuToolStripSeparator1";
			this->m_sprTextMenuToolStripSeparator1->Size = System::Drawing::Size(141, 6);
			// 
			// m_itmInsertToolStripMenuItem
			// 
			this->m_itmInsertToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->m_itmRandomToolStripMenuItem, 
				this->m_itmValueToolStripMenuItem});
			this->m_itmInsertToolStripMenuItem->Name = L"m_itmInsertToolStripMenuItem";
			this->m_itmInsertToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->m_itmInsertToolStripMenuItem->Text = L"Insert";
			// 
			// m_itmRandomToolStripMenuItem
			// 
			this->m_itmRandomToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->m_itmByteToolStripMenuItem, 
				this->m_itmInt16ToolStripMenuItem, this->m_itmInt32ToolStripMenuItem, this->m_sprRandomMenuToolStripSeparator1, this->m_itmAsciiToolStripMenuItem, 
				this->m_itmStringToolStripMenuItem});
			this->m_itmRandomToolStripMenuItem->Name = L"m_itmRandomToolStripMenuItem";
			this->m_itmRandomToolStripMenuItem->Size = System::Drawing::Size(132, 22);
			this->m_itmRandomToolStripMenuItem->Text = L"Random";
			// 
			// m_itmByteToolStripMenuItem
			// 
			this->m_itmByteToolStripMenuItem->Name = L"m_itmByteToolStripMenuItem";
			this->m_itmByteToolStripMenuItem->Size = System::Drawing::Size(164, 22);
			this->m_itmByteToolStripMenuItem->Text = L"Byte";
			this->m_itmByteToolStripMenuItem->ToolTipText = L"Insert a random byte value";
			this->m_itmByteToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnRandomByteClick);
			// 
			// m_itmInt16ToolStripMenuItem
			// 
			this->m_itmInt16ToolStripMenuItem->Name = L"m_itmInt16ToolStripMenuItem";
			this->m_itmInt16ToolStripMenuItem->Size = System::Drawing::Size(164, 22);
			this->m_itmInt16ToolStripMenuItem->Text = L"16-bit Integer";
			this->m_itmInt16ToolStripMenuItem->ToolTipText = L"Insert a 16-bit integer value";
			this->m_itmInt16ToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnRandomInt16Click);
			// 
			// m_itmInt32ToolStripMenuItem
			// 
			this->m_itmInt32ToolStripMenuItem->Name = L"m_itmInt32ToolStripMenuItem";
			this->m_itmInt32ToolStripMenuItem->Size = System::Drawing::Size(164, 22);
			this->m_itmInt32ToolStripMenuItem->Text = L"32-bit Integer";
			this->m_itmInt32ToolStripMenuItem->ToolTipText = L"Insert a 32-bit integer value";
			this->m_itmInt32ToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnRandomInt32Click);
			// 
			// m_sprRandomMenuToolStripSeparator1
			// 
			this->m_sprRandomMenuToolStripSeparator1->Name = L"m_sprRandomMenuToolStripSeparator1";
			this->m_sprRandomMenuToolStripSeparator1->Size = System::Drawing::Size(161, 6);
			// 
			// m_itmAsciiToolStripMenuItem
			// 
			this->m_itmAsciiToolStripMenuItem->Name = L"m_itmAsciiToolStripMenuItem";
			this->m_itmAsciiToolStripMenuItem->Size = System::Drawing::Size(164, 22);
			this->m_itmAsciiToolStripMenuItem->Text = L"ASCII";
			this->m_itmAsciiToolStripMenuItem->ToolTipText = L"Insert an ASCII character";
			this->m_itmAsciiToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnRandomAsciiClick);
			// 
			// m_itmStringToolStripMenuItem
			// 
			this->m_itmStringToolStripMenuItem->Name = L"m_itmStringToolStripMenuItem";
			this->m_itmStringToolStripMenuItem->Size = System::Drawing::Size(164, 22);
			this->m_itmStringToolStripMenuItem->Text = L"String";
			this->m_itmStringToolStripMenuItem->ToolTipText = L"Insert a random string";
			this->m_itmStringToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnRandomStringClick);
			// 
			// m_itmValueToolStripMenuItem
			// 
			this->m_itmValueToolStripMenuItem->Name = L"m_itmValueToolStripMenuItem";
			this->m_itmValueToolStripMenuItem->Size = System::Drawing::Size(132, 22);
			this->m_itmValueToolStripMenuItem->Text = L"Value";
			this->m_itmValueToolStripMenuItem->DropDownItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &ZApplication::OnValueDropDownItemClicked);
			// 
			// m_itmTransformToolStripMenuItem
			// 
			this->m_itmTransformToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->m_itmToInt16ToolStripMenuItem, 
				this->m_itmToInt32ToolStripMenuItem, this->m_sprTransformToolStripSeparator1, this->m_itmToAsciiToolStripMenuItem, this->m_itmToStringToolStripMenuItem});
			this->m_itmTransformToolStripMenuItem->Name = L"m_itmTransformToolStripMenuItem";
			this->m_itmTransformToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->m_itmTransformToolStripMenuItem->Text = L"Transform";
			// 
			// m_itmToInt16ToolStripMenuItem
			// 
			this->m_itmToInt16ToolStripMenuItem->Enabled = false;
			this->m_itmToInt16ToolStripMenuItem->Name = L"m_itmToInt16ToolStripMenuItem";
			this->m_itmToInt16ToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			this->m_itmToInt16ToolStripMenuItem->Text = L"To 16-bit Integer";
			this->m_itmToInt16ToolStripMenuItem->ToolTipText = L"Convert the selected 2-byte sequnce into a 16-bit integer";
			this->m_itmToInt16ToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnToIn16Click);
			// 
			// m_itmToInt32ToolStripMenuItem
			// 
			this->m_itmToInt32ToolStripMenuItem->Enabled = false;
			this->m_itmToInt32ToolStripMenuItem->Name = L"m_itmToInt32ToolStripMenuItem";
			this->m_itmToInt32ToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			this->m_itmToInt32ToolStripMenuItem->Text = L"To 32-bit Integer";
			this->m_itmToInt32ToolStripMenuItem->ToolTipText = L"Convert the selected 4-byte sequence into a 32-bit integer";
			this->m_itmToInt32ToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnToInt32Click);
			// 
			// m_sprTransformToolStripSeparator1
			// 
			this->m_sprTransformToolStripSeparator1->Name = L"m_sprTransformToolStripSeparator1";
			this->m_sprTransformToolStripSeparator1->Size = System::Drawing::Size(179, 6);
			// 
			// m_itmToAsciiToolStripMenuItem
			// 
			this->m_itmToAsciiToolStripMenuItem->Enabled = false;
			this->m_itmToAsciiToolStripMenuItem->Name = L"m_itmToAsciiToolStripMenuItem";
			this->m_itmToAsciiToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			this->m_itmToAsciiToolStripMenuItem->Text = L"To ASCII";
			this->m_itmToAsciiToolStripMenuItem->ToolTipText = L"Convert the selected byte into an ASCII character";
			this->m_itmToAsciiToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnToAsciiClick);
			// 
			// m_itmToStringToolStripMenuItem
			// 
			this->m_itmToStringToolStripMenuItem->Enabled = false;
			this->m_itmToStringToolStripMenuItem->Name = L"m_itmToStringToolStripMenuItem";
			this->m_itmToStringToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			this->m_itmToStringToolStripMenuItem->Text = L"To String";
			this->m_itmToStringToolStripMenuItem->ToolTipText = L"Convert the selected bytes into a string (if possible)";
			this->m_itmToStringToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnToStringClick);
			// 
			// m_sprTextMenuToolStripSeparator2
			// 
			this->m_sprTextMenuToolStripSeparator2->Name = L"m_sprTextMenuToolStripSeparator2";
			this->m_sprTextMenuToolStripSeparator2->Size = System::Drawing::Size(141, 6);
			// 
			// m_itmCutToolStripMenuItem
			// 
			this->m_itmCutToolStripMenuItem->Enabled = false;
			this->m_itmCutToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_itmCutToolStripMenuItem.Image")));
			this->m_itmCutToolStripMenuItem->Name = L"m_itmCutToolStripMenuItem";
			this->m_itmCutToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->m_itmCutToolStripMenuItem->Text = L"Cut";
			this->m_itmCutToolStripMenuItem->ToolTipText = L"Cut the selected text and copy it to the clipboard";
			this->m_itmCutToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnTextCutClick);
			// 
			// m_itmCopyToolStripMenuItem
			// 
			this->m_itmCopyToolStripMenuItem->Enabled = false;
			this->m_itmCopyToolStripMenuItem->Name = L"m_itmCopyToolStripMenuItem";
			this->m_itmCopyToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->m_itmCopyToolStripMenuItem->Text = L"Copy";
			this->m_itmCopyToolStripMenuItem->ToolTipText = L"Copy the selected text to the clipboard";
			this->m_itmCopyToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnTextCopyClick);
			// 
			// m_itmPasteToolStripMenuItem
			// 
			this->m_itmPasteToolStripMenuItem->Enabled = false;
			this->m_itmPasteToolStripMenuItem->Name = L"m_itmPasteToolStripMenuItem";
			this->m_itmPasteToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->m_itmPasteToolStripMenuItem->Text = L"Paste";
			this->m_itmPasteToolStripMenuItem->ToolTipText = L"Paste text from the clipboard";
			this->m_itmPasteToolStripMenuItem->Click += gcnew System::EventHandler(this, &ZApplication::OnTextPasteClick);
			// 
			// m_lblPacket1
			// 
			this->m_lblPacket1->Location = System::Drawing::Point(5, 5);
			this->m_lblPacket1->Margin = System::Windows::Forms::Padding(0);
			this->m_lblPacket1->Name = L"m_lblPacket1";
			this->m_lblPacket1->Size = System::Drawing::Size(55, 21);
			this->m_lblPacket1->TabIndex = 0;
			this->m_lblPacket1->Text = L"Packet";
			this->m_lblPacket1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_tbpSend
			// 
			this->m_tbpSend->BackColor = System::Drawing::Color::White;
			this->m_tbpSend->Controls->Add(this->m_lstSendList);
			this->m_tbpSend->Controls->Add(this->m_pnlContainer2);
			this->m_tbpSend->ImageIndex = 1;
			this->m_tbpSend->Location = System::Drawing::Point(4, 22);
			this->m_tbpSend->Margin = System::Windows::Forms::Padding(1);
			this->m_tbpSend->Name = L"m_tbpSend";
			this->m_tbpSend->Padding = System::Windows::Forms::Padding(3, 3, 3, 1);
			this->m_tbpSend->Size = System::Drawing::Size(528, 341);
			this->m_tbpSend->TabIndex = 1;
			this->m_tbpSend->Text = L"Sent";
			this->m_tbpSend->ToolTipText = L"View all packet sent to the server";
			// 
			// m_lstSendList
			// 
			this->m_lstSendList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->m_hdrSendImage, 
				this->m_hdrSendSize, this->m_hdrSendCode, this->m_hdrSendData});
			this->m_lstSendList->ContextMenuStrip = this->m_ctxItemMenu;
			this->m_lstSendList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_lstSendList->FullRowSelect = true;
			this->m_lstSendList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->m_lstSendList->Location = System::Drawing::Point(3, 3);
			this->m_lstSendList->Margin = System::Windows::Forms::Padding(0);
			this->m_lstSendList->Name = L"m_lstSendList";
			this->m_lstSendList->Size = System::Drawing::Size(522, 279);
			this->m_lstSendList->TabIndex = 1;
			this->m_lstSendList->UseCompatibleStateImageBehavior = false;
			this->m_lstSendList->View = System::Windows::Forms::View::Details;
			this->m_lstSendList->ItemMouseHover += gcnew System::Windows::Forms::ListViewItemMouseHoverEventHandler(this, &ZApplication::OnListItemMouseHover);
			this->m_lstSendList->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &ZApplication::OnSendListItemSelectionChanged);
			this->m_lstSendList->ColumnWidthChanging += gcnew System::Windows::Forms::ColumnWidthChangingEventHandler(this, &ZApplication::OnListColumnWidthChanging);
			// 
			// m_hdrSendImage
			// 
			this->m_hdrSendImage->Text = L"";
			this->m_hdrSendImage->Width = 0;
			// 
			// m_hdrSendSize
			// 
			this->m_hdrSendSize->Text = L"Size";
			this->m_hdrSendSize->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrSendSize->Width = 45;
			// 
			// m_hdrSendCode
			// 
			this->m_hdrSendCode->Text = L"Code";
			this->m_hdrSendCode->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrSendCode->Width = 65;
			// 
			// m_hdrSendData
			// 
			this->m_hdrSendData->Text = L"Data";
			this->m_hdrSendData->Width = 395;
			// 
			// m_pnlContainer2
			// 
			this->m_pnlContainer2->Controls->Add(this->m_btnInjectSend);
			this->m_pnlContainer2->Controls->Add(this->m_btnFilterSend);
			this->m_pnlContainer2->Controls->Add(this->m_btnIgnoreSend);
			this->m_pnlContainer2->Controls->Add(this->m_btnBlockSend);
			this->m_pnlContainer2->Controls->Add(this->m_lblFilter2);
			this->m_pnlContainer2->Controls->Add(this->m_chxFilterEmptySend);
			this->m_pnlContainer2->Controls->Add(this->m_chxFilterNullSend);
			this->m_pnlContainer2->Controls->Add(this->m_btnGetSendPacket);
			this->m_pnlContainer2->Controls->Add(this->m_txtSendPacket);
			this->m_pnlContainer2->Controls->Add(this->m_lblPacket2);
			this->m_pnlContainer2->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->m_pnlContainer2->Location = System::Drawing::Point(3, 282);
			this->m_pnlContainer2->Margin = System::Windows::Forms::Padding(0);
			this->m_pnlContainer2->Name = L"m_pnlContainer2";
			this->m_pnlContainer2->Padding = System::Windows::Forms::Padding(2);
			this->m_pnlContainer2->Size = System::Drawing::Size(522, 58);
			this->m_pnlContainer2->TabIndex = 2;
			// 
			// m_btnInjectSend
			// 
			this->m_btnInjectSend->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnInjectSend->Enabled = false;
			this->m_btnInjectSend->Location = System::Drawing::Point(267, 30);
			this->m_btnInjectSend->Margin = System::Windows::Forms::Padding(0);
			this->m_btnInjectSend->Name = L"m_btnInjectSend";
			this->m_btnInjectSend->Size = System::Drawing::Size(65, 25);
			this->m_btnInjectSend->TabIndex = 3;
			this->m_btnInjectSend->Text = L"Inject";
			this->m_ttpToolTip->SetToolTip(this->m_btnInjectSend, L"Inject a packet into the sent packets stream");
			this->m_btnInjectSend->UseVisualStyleBackColor = true;
			this->m_btnInjectSend->Click += gcnew System::EventHandler(this, &ZApplication::OnInjectSendClick);
			// 
			// m_btnFilterSend
			// 
			this->m_btnFilterSend->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnFilterSend->Enabled = false;
			this->m_btnFilterSend->Location = System::Drawing::Point(332, 30);
			this->m_btnFilterSend->Margin = System::Windows::Forms::Padding(0);
			this->m_btnFilterSend->Name = L"m_btnFilterSend";
			this->m_btnFilterSend->Size = System::Drawing::Size(65, 25);
			this->m_btnFilterSend->TabIndex = 4;
			this->m_btnFilterSend->Text = L"Filter";
			this->m_ttpToolTip->SetToolTip(this->m_btnFilterSend, L"Search through the packets for specific data");
			this->m_btnFilterSend->UseVisualStyleBackColor = true;
			this->m_btnFilterSend->Click += gcnew System::EventHandler(this, &ZApplication::OnFilterSendClick);
			// 
			// m_btnIgnoreSend
			// 
			this->m_btnIgnoreSend->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnIgnoreSend->Enabled = false;
			this->m_btnIgnoreSend->Location = System::Drawing::Point(397, 30);
			this->m_btnIgnoreSend->Margin = System::Windows::Forms::Padding(0);
			this->m_btnIgnoreSend->Name = L"m_btnIgnoreSend";
			this->m_btnIgnoreSend->Size = System::Drawing::Size(65, 25);
			this->m_btnIgnoreSend->TabIndex = 5;
			this->m_btnIgnoreSend->Text = L"Ignore";
			this->m_ttpToolTip->SetToolTip(this->m_btnIgnoreSend, L"Add a specific packet or pattern to the ignore list");
			this->m_btnIgnoreSend->UseVisualStyleBackColor = true;
			this->m_btnIgnoreSend->Click += gcnew System::EventHandler(this, &ZApplication::OnIgnoreSendClick);
			// 
			// m_btnBlockSend
			// 
			this->m_btnBlockSend->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnBlockSend->Enabled = false;
			this->m_btnBlockSend->Location = System::Drawing::Point(462, 30);
			this->m_btnBlockSend->Margin = System::Windows::Forms::Padding(0);
			this->m_btnBlockSend->Name = L"m_btnBlockSend";
			this->m_btnBlockSend->Size = System::Drawing::Size(65, 25);
			this->m_btnBlockSend->TabIndex = 6;
			this->m_btnBlockSend->Text = L"Block";
			this->m_ttpToolTip->SetToolTip(this->m_btnBlockSend, L"Add a specific packet or pattern to the blocked list");
			this->m_btnBlockSend->UseVisualStyleBackColor = true;
			this->m_btnBlockSend->Click += gcnew System::EventHandler(this, &ZApplication::OnBlockSendClick);
			// 
			// m_lblFilter2
			// 
			this->m_lblFilter2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_lblFilter2.Image")));
			this->m_lblFilter2->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->m_lblFilter2->Location = System::Drawing::Point(5, 30);
			this->m_lblFilter2->Margin = System::Windows::Forms::Padding(0);
			this->m_lblFilter2->Name = L"m_lblFilter2";
			this->m_lblFilter2->Size = System::Drawing::Size(56, 25);
			this->m_lblFilter2->TabIndex = 3;
			this->m_lblFilter2->Text = L"Filter";
			this->m_lblFilter2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// m_chxFilterEmptySend
			// 
			this->m_chxFilterEmptySend->Location = System::Drawing::Point(150, 30);
			this->m_chxFilterEmptySend->Margin = System::Windows::Forms::Padding(0);
			this->m_chxFilterEmptySend->Name = L"m_chxFilterEmptySend";
			this->m_chxFilterEmptySend->Padding = System::Windows::Forms::Padding(4, 0, 0, 0);
			this->m_chxFilterEmptySend->Size = System::Drawing::Size(95, 25);
			this->m_chxFilterEmptySend->TabIndex = 0;
			this->m_chxFilterEmptySend->TabStop = false;
			this->m_chxFilterEmptySend->Text = L"Empty data";
			this->m_ttpToolTip->SetToolTip(this->m_chxFilterEmptySend, L"Filter out packets that contain no data");
			this->m_chxFilterEmptySend->UseVisualStyleBackColor = true;
			this->m_chxFilterEmptySend->CheckedChanged += gcnew System::EventHandler(this, &ZApplication::OnFilterEmptyCheckedChanged);
			// 
			// m_chxFilterNullSend
			// 
			this->m_chxFilterNullSend->Location = System::Drawing::Point(65, 30);
			this->m_chxFilterNullSend->Margin = System::Windows::Forms::Padding(0);
			this->m_chxFilterNullSend->Name = L"m_chxFilterNullSend";
			this->m_chxFilterNullSend->Padding = System::Windows::Forms::Padding(4, 0, 0, 0);
			this->m_chxFilterNullSend->Size = System::Drawing::Size(80, 25);
			this->m_chxFilterNullSend->TabIndex = 0;
			this->m_chxFilterNullSend->TabStop = false;
			this->m_chxFilterNullSend->Text = L"Null data";
			this->m_ttpToolTip->SetToolTip(this->m_chxFilterNullSend, L"Filter out packets that contain only NULL data");
			this->m_chxFilterNullSend->UseVisualStyleBackColor = true;
			this->m_chxFilterNullSend->CheckedChanged += gcnew System::EventHandler(this, &ZApplication::OnFilterNullSendCheckedChanged);
			// 
			// m_btnGetSendPacket
			// 
			this->m_btnGetSendPacket->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->m_btnGetSendPacket->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->m_btnGetSendPacket->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_btnGetSendPacket.Image")));
			this->m_btnGetSendPacket->Location = System::Drawing::Point(497, 5);
			this->m_btnGetSendPacket->Margin = System::Windows::Forms::Padding(0);
			this->m_btnGetSendPacket->Name = L"m_btnGetSendPacket";
			this->m_btnGetSendPacket->Size = System::Drawing::Size(30, 21);
			this->m_btnGetSendPacket->TabIndex = 0;
			this->m_btnGetSendPacket->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->m_btnGetSendPacket->Click += gcnew System::EventHandler(this, &ZApplication::OnGetSendPacketClick);
			// 
			// m_txtSendPacket
			// 
			this->m_txtSendPacket->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_txtSendPacket->ContextMenuStrip = this->m_ctxTextMenu;
			this->m_txtSendPacket->Location = System::Drawing::Point(60, 5);
			this->m_txtSendPacket->Margin = System::Windows::Forms::Padding(0);
			this->m_txtSendPacket->MaxLength = 0;
			this->m_txtSendPacket->Name = L"m_txtSendPacket";
			this->m_txtSendPacket->Size = System::Drawing::Size(437, 21);
			this->m_txtSendPacket->TabIndex = 2;
			this->m_txtSendPacket->TextChanged += gcnew System::EventHandler(this, &ZApplication::OnPacketTextChanged);
			this->m_txtSendPacket->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &ZApplication::OnSendPacketMouseDoubleClick);
			this->m_txtSendPacket->Enter += gcnew System::EventHandler(this, &ZApplication::OnSendPacketEnter);
			// 
			// m_lblPacket2
			// 
			this->m_lblPacket2->Location = System::Drawing::Point(5, 5);
			this->m_lblPacket2->Margin = System::Windows::Forms::Padding(0);
			this->m_lblPacket2->Name = L"m_lblPacket2";
			this->m_lblPacket2->Size = System::Drawing::Size(55, 21);
			this->m_lblPacket2->TabIndex = 0;
			this->m_lblPacket2->Text = L"Packet";
			this->m_lblPacket2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_tbpBoth
			// 
			this->m_tbpBoth->BackColor = System::Drawing::Color::White;
			this->m_tbpBoth->Controls->Add(this->m_lstBothList);
			this->m_tbpBoth->ImageIndex = 2;
			this->m_tbpBoth->Location = System::Drawing::Point(4, 22);
			this->m_tbpBoth->Margin = System::Windows::Forms::Padding(1);
			this->m_tbpBoth->Name = L"m_tbpBoth";
			this->m_tbpBoth->Padding = System::Windows::Forms::Padding(3);
			this->m_tbpBoth->Size = System::Drawing::Size(528, 341);
			this->m_tbpBoth->TabIndex = 2;
			this->m_tbpBoth->Text = L"History";
			this->m_tbpBoth->ToolTipText = L"All packets received and sent to and from the server";
			// 
			// m_lstBothList
			// 
			this->m_lstBothList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {this->m_hdrBothImage, 
				this->m_hdrBothSize, this->m_hdrBothCode, this->m_hdrBothData});
			this->m_lstBothList->ContextMenuStrip = this->m_ctxItemMenu;
			this->m_lstBothList->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_lstBothList->FullRowSelect = true;
			this->m_lstBothList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->m_lstBothList->Location = System::Drawing::Point(3, 3);
			this->m_lstBothList->Margin = System::Windows::Forms::Padding(0);
			this->m_lstBothList->Name = L"m_lstBothList";
			this->m_lstBothList->Size = System::Drawing::Size(522, 335);
			this->m_lstBothList->StateImageList = this->m_lstPacketImages;
			this->m_lstBothList->TabIndex = 1;
			this->m_lstBothList->TabStop = false;
			this->m_lstBothList->UseCompatibleStateImageBehavior = false;
			this->m_lstBothList->View = System::Windows::Forms::View::Details;
			this->m_lstBothList->ItemMouseHover += gcnew System::Windows::Forms::ListViewItemMouseHoverEventHandler(this, &ZApplication::OnListItemMouseHover);
			this->m_lstBothList->ItemSelectionChanged += gcnew System::Windows::Forms::ListViewItemSelectionChangedEventHandler(this, &ZApplication::OnBothListItemSelectionChanged);
			this->m_lstBothList->ColumnWidthChanging += gcnew System::Windows::Forms::ColumnWidthChangingEventHandler(this, &ZApplication::OnListColumnWidthChanging);
			// 
			// m_hdrBothImage
			// 
			this->m_hdrBothImage->Text = L"";
			this->m_hdrBothImage->Width = 20;
			// 
			// m_hdrBothSize
			// 
			this->m_hdrBothSize->Text = L"Size";
			this->m_hdrBothSize->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrBothSize->Width = 45;
			// 
			// m_hdrBothCode
			// 
			this->m_hdrBothCode->Text = L"Code";
			this->m_hdrBothCode->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->m_hdrBothCode->Width = 65;
			// 
			// m_hdrBothData
			// 
			this->m_hdrBothData->Text = L"Data";
			this->m_hdrBothData->Width = 375;
			// 
			// m_lstPacketImages
			// 
			this->m_lstPacketImages->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"m_lstPacketImages.ImageStream")));
			this->m_lstPacketImages->TransparentColor = System::Drawing::Color::Transparent;
			this->m_lstPacketImages->Images->SetKeyName(0, L"green_arrow_down.png");
			this->m_lstPacketImages->Images->SetKeyName(1, L"blue_arrow_down.png");
			this->m_lstPacketImages->Images->SetKeyName(2, L"books.png");
			// 
			// m_lblBanner
			// 
			this->m_lblBanner->Dock = System::Windows::Forms::DockStyle::Fill;
			this->m_lblBanner->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"m_lblBanner.Image")));
			this->m_lblBanner->Location = System::Drawing::Point(0, 0);
			this->m_lblBanner->Margin = System::Windows::Forms::Padding(0);
			this->m_lblBanner->Name = L"m_lblBanner";
			this->m_lblBanner->Size = System::Drawing::Size(548, 53);
			this->m_lblBanner->TabIndex = 0;
			this->m_lblBanner->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// m_ntiSystemTray
			// 
			this->m_ntiSystemTray->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"m_ntiSystemTray.Icon")));
			this->m_ntiSystemTray->Text = L"Z";
			this->m_ntiSystemTray->Click += gcnew System::EventHandler(this, &ZApplication::OnSystemTrayClick);
			// 
			// m_ttpToolTip
			// 
			this->m_ttpToolTip->Popup += gcnew System::Windows::Forms::PopupEventHandler(this, &ZApplication::OnToolTipPopup);
			// 
			// ZApplication
			// 
			this->ClientSize = System::Drawing::Size(548, 548);
			this->Controls->Add(this->m_splConatiner);
			this->Controls->Add(this->m_sbrStrip);
			this->Controls->Add(this->m_mbrStrip);
			this->Font = (gcnew System::Drawing::Font(L"Verdana", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->m_mbrStrip;
			this->MaximizeBox = false;
			this->MinimumSize = System::Drawing::Size(556, 575);
			this->Name = L"ZApplication";
			this->Text = L"Z - The Packet Inspector";
			this->TopMost = true;
			this->m_mbrStrip->ResumeLayout(false);
			this->m_mbrStrip->PerformLayout();
			this->m_sbrStrip->ResumeLayout(false);
			this->m_sbrStrip->PerformLayout();
			this->m_splConatiner->Panel1->ResumeLayout(false);
			this->m_splConatiner->Panel2->ResumeLayout(false);
			this->m_splConatiner->ResumeLayout(false);
			this->m_tbPackets->ResumeLayout(false);
			this->m_tbpRecv->ResumeLayout(false);
			this->m_ctxItemMenu->ResumeLayout(false);
			this->m_pnlContainer1->ResumeLayout(false);
			this->m_pnlContainer1->PerformLayout();
			this->m_ctxTextMenu->ResumeLayout(false);
			this->m_tbpSend->ResumeLayout(false);
			this->m_pnlContainer2->ResumeLayout(false);
			this->m_pnlContainer2->PerformLayout();
			this->m_tbpBoth->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	void OnMemoryClick ( Object^ sender, EventArgs^ e );
			 
void OnQuitGameClick ( Object^ sender, EventArgs^ e );
		 
void OnExitGameClick ( Object^ sender, EventArgs^ e );
		 
void OnExitClick ( Object^ sender, EventArgs^ e );
		 
void OnViewRecvClick ( Object^ sender, EventArgs^ e );
		 
void OnViewSentClick ( Object^ sender, EventArgs^ e );
		 
void OnTemplatesClick ( Object^ sender, EventArgs^ e );
		 
void OnBuilderClick ( Object^ sender, EventArgs^ e );
		 
void OnHistoryClick ( Object^ sender, EventArgs^ e );
		 
void OnBlockedRecvClick ( Object^ sender, EventArgs^ e );
		 
void OnIgnoredRecvClick ( Object^ sender, EventArgs^ e );
		 
void OnBlockedSendClick ( Object^ sender, EventArgs^ e );
		 
void OnIgnoredSendClick ( Object^ sender, EventArgs^ e );
		 
void OnCustomClick ( Object^ sender, EventArgs^ e );
		 
void OnExecuteClick ( Object^ sender, EventArgs^ e );
		 
void OnFloodControlClick ( Object^ sender, EventArgs^ e );
	 
void OnHelpDropDownItemClicked ( Object^ sender, ToolStripItemClickedEventArgs^ e );
		 
void OnListItemMouseHover ( Object^ sender, ListViewItemMouseHoverEventArgs^ e );
		 
void OnRecvListItemSelectionChanged ( Object^ sender, ListViewItemSelectionChangedEventArgs^ e );
		 
void OnRecvPacketEnter ( Object^ sender, EventArgs^ e );
		 
void OnGetRecvPacketClick ( Object^ sender, EventArgs^ e );
		 
void OnFilterNullRecvCheckedChanged ( Object^ sender, EventArgs^ e );
		 
void OnFilterEmptyRecvCheckedChanged ( Object^ sender, EventArgs^ e );
		 
void OnInjectRecvClick ( Object^ sender, EventArgs^ e );
		 
void OnFilterRecvClick ( Object^ sender, EventArgs^ e );
		 
void OnIgnoreRecvClick ( Object^ sender, EventArgs^ e );
		 
void OnBlockRecvClick ( Object^ sender, EventArgs^ e );
		 
void OnSendPacketEnter ( Object^ sender, EventArgs^ e );
		 
void OnGetSendPacketClick ( Object^ sender, EventArgs^ e );
		 
void OnFilterNullSendCheckedChanged ( Object^ sender, EventArgs^ e );
		 
void OnFilterEmptyCheckedChanged ( Object^ sender, EventArgs^ e );
		 
void OnInjectSendClick ( Object^ sender, EventArgs^ e );
		 
void OnFilterSendClick ( Object^ sender, EventArgs^ e );
		 
void OnIgnoreSendClick ( Object^ sender, EventArgs^ e );
		 
void OnBlockSendClick ( Object^ sender, EventArgs^ e );
		 
void OnSendListItemSelectionChanged ( Object^ sender, ListViewItemSelectionChangedEventArgs^ e );
		 
void OnBothListItemSelectionChanged ( Object^ sender, ListViewItemSelectionChangedEventArgs^ e );
		 
void OnCreateTemplateClick ( Object^ sender, EventArgs^ e );
		 
void OnAppendFavoritesClick ( Object^ sender, EventArgs^ e );
		 
void OnCollectDropDownItemClicked ( Object^ sender, ToolStripItemClickedEventArgs^ e );
		 
void OnRemoveItemClick ( Object^ sender, EventArgs^ e );
		 
void OnClearItemsClick ( Object^ sender, EventArgs^ e );
		 

void OnItemMenuOpening ( Object^ sender, CancelEventArgs^ e );
		 
void OnTextFormatClick ( Object^ sender, EventArgs^ e );
		 
void OnTextCutClick ( Object^ sender, EventArgs^ e );
		 
void OnTextCopyClick ( Object^ sender, EventArgs^ e );
		 
void OnTextPasteClick ( Object^ sender, EventArgs^ e );
		 		 
void OnValueDropDownItemClicked ( Object^ sender, ToolStripItemClickedEventArgs^ e );
		 
void OnTextMenuOpening ( Object^ sender, CancelEventArgs^ e );
		 
void OnPacketTextChanged ( Object^ sender, EventArgs^ e );
		 
void OnListColumnWidthChanging ( Object^ sender, ColumnWidthChangingEventArgs^ e );
		 
void OnCollectionsDropDrownItemClicked ( Object^ sender, ToolStripItemClickedEventArgs^ e );
		 
void OnSystemTrayClick ( Object^ sender, EventArgs^ e );
		 
void OnToolTipPopup ( Object^ sender, PopupEventArgs^ e );
		 
void OnToIn16Click ( Object^ sender, EventArgs^ e );
		 
void OnToInt32Click ( Object^ sender, EventArgs^ e );
		 
void OnToAsciiClick ( Object^ sender, EventArgs^ e );
		 
void OnToStringClick ( Object^ sender, EventArgs^ e );
		 
void OnAlwaysOnTopClick ( Object^ sender, EventArgs^ e );
		 
void OnTransparentClick ( Object^ sender, EventArgs^ e );

void OnTopLevelWindowClick ( Object^ sender, EventArgs^ e );
		 
void OnSystemTrayIconClick ( Object^ sender, EventArgs^ e );
		 
void OnMinimizeOnCloseClick ( Object^ sender, EventArgs^ e );
		 
void OnHideBannerAdClick ( Object^ sender, EventArgs^ e );
		 
void OnRecvPacketMouseDoubleClick ( Object^ sender, MouseEventArgs^ e );

void OnSendPacketMouseDoubleClick ( Object^ sender, MouseEventArgs^ e );

void OnRandomByteClick ( Object^ sender, EventArgs^ e );

void OnRandomInt16Click ( Object^ sender, EventArgs^ e );

void OnRandomInt32Click ( Object^ sender, EventArgs^ e );

void OnRandomAsciiClick ( Object^ sender, EventArgs^ e );

void OnRandomStringClick ( Object^ sender, EventArgs^ e );

};
}

#endif /* __ZApplication_h__ */

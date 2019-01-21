// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2018-2019 The TWINS developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZTWINSCONTROLDIALOG_H
#define ZTWINSCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "primitives/zerocoin.h"
#include "privacydialog.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZTWINSControlDialog;
}

class CZTWINSControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZTWINSControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZTWINSControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZTWINSControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZTWINSControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZTWINSControlDialog(QWidget *parent);
    ~ZTWINSControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZTWINSControlDialog *ui;
    WalletModel* model;
    PrivacyDialog* privacyDialog;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZTWINSControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZTWINSCONTROLDIALOG_H

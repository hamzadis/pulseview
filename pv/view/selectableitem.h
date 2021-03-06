/*
 * This file is part of the PulseView project.
 *
 * Copyright (C) 2013 Joel Holdsworth <joel@airwebreathe.org.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef PULSEVIEW_PV_SELECTABLEITEM_H
#define PULSEVIEW_PV_SELECTABLEITEM_H

#include <list>

#include <QPen>

class QAction;
class QMenu;
class QWidget;

namespace pv {

namespace widgets {
class Popup;
}

namespace view {

class SelectableItem : public QObject
{
	Q_OBJECT

private:
	static const int HighlightRadius;

public:
	SelectableItem();

public:
	/**
	 * Returns true if the item has been selected by the user.
	 */
	bool selected() const;

	/**
	 * Selects or deselects the signal.
	 */
	void select(bool select = true);

	/**
	 * Returns true if the item is being dragged.
	 */
	bool dragging() const;

	/**
	 * Retunrns the current drag point.
	 */
	QPoint drag_point() const;

	/**
	 * Sets this item into the dragged state.
	 */
	void drag();

	/**
	 * Sets this item into the un-dragged state.
	 */
	void drag_release();

	/**
	 * Get the drag point.
	 */
	virtual QPoint point() const = 0;

public:
	virtual QMenu* create_context_menu(QWidget *parent);

	virtual pv::widgets::Popup* create_popup(QWidget *parent) = 0;

	virtual void delete_pressed();

protected:
	static QPen highlight_pen();

protected:
	QWidget *_context_parent;

private:
	bool _selected;
	QPoint _drag_point;
};

} // namespace view
} // namespace pv

#endif // PULSEVIEW_PV_SELECTABLEITEM_H

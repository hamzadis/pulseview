/*
 * This file is part of the PulseView project.
 *
 * Copyright (C) 2014 Joel Holdsworth <joel@airwebreathe.org.uk>
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

#include <cassert>

#include "rowitem.h"
#include "rowitemowner.h"

using std::max;
using std::make_pair;
using std::min;
using std::pair;
using std::shared_ptr;
using std::vector;

namespace pv {
namespace view {

vector< shared_ptr<RowItem> >& RowItemOwner::child_items()
{
	return _items;
}

const vector< shared_ptr<RowItem> >& RowItemOwner::child_items() const
{
	return _items;
}

void RowItemOwner::clear_child_items()
{
	for (auto &i : _items) {
		assert(i->owner() == this);
		i->set_owner(nullptr);
	}
	_items.clear();
}

void RowItemOwner::add_child_item(std::shared_ptr<RowItem> item)
{
	assert(!item->owner());
	item->set_owner(this);
	_items.push_back(item);

	extents_changed(true, true);
}

void RowItemOwner::remove_child_item(std::shared_ptr<RowItem> item)
{
	assert(item->owner() == this);
	item->set_owner(nullptr);
	auto iter = std::find(_items.begin(), _items.end(), item);
	assert(iter != _items.end());
	_items.erase(iter);

	extents_changed(true, true);
}

RowItemOwner::iterator RowItemOwner::begin()
{
	return iterator(this, _items.begin());
}

RowItemOwner::iterator RowItemOwner::end()
{
	return iterator(this);
}

RowItemOwner::const_iterator RowItemOwner::begin() const
{
	return const_iterator(this, _items.cbegin());
}

RowItemOwner::const_iterator RowItemOwner::end() const
{
	return const_iterator(this);
}

pair<int, int> RowItemOwner::v_extents() const
{
	pair<int, int> extents(0, 0);
	for (const shared_ptr<RowItem> r : child_items()) {
		assert(r);
		if (!r->enabled())
			continue;

		const int child_offset = r->layout_v_offset();
		const pair<int, int> child_extents = r->v_extents();
		extents.first = min(child_extents.first + child_offset,
			extents.first);
		extents.second = max(child_extents.second + child_offset,
			extents.second);
	}

	return extents;
}

void RowItemOwner::restack_items()
{
}

} // view
} // pv

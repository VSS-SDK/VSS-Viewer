/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#ifndef ICONTROL_H_
#define ICONTROL_H_

class IControl {
public:

	IControl();

	void virtual pauseOrStart();
	void virtual changeCamera();
	void virtual selectDrawer();
	void virtual deSelectDrawer();
	void virtual moveDrawer();
	void virtual rotateDrawer();
};

#endif // ICONTROL_H_

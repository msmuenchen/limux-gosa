<?php
/*
  This code is part of GOsa (https://gosa.gonicus.de)
  Copyright (C) 2003  Cajus Pollmeier

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* Remove locks created by this plugin
*/
if ($remove_lock){
  if(session::is_set('mailqueue')){
    // Nothing to unlock here
  }
}

/* Remove this plugin from session
*/
if ( $cleanup ){
  session::un_set('mailqueue');
}else{
    /* Reset requested? */
    if (isset($_GET['reset']) && $_GET['reset'] == 1){
        session::un_set ('sudoManagement');
    }

	/* Create mailqueue object on demand */
	if (!session::is_set('mailqueue')){
		$ui = get_userinfo();
		$mailqueue= new mailqueue ($config);
		$mailqueue->set_acl_category("mailqueue");
		
		/* Check root dn and user dn for acl informations */
		$mailqueue->set_acl_base($config->current['BASE']);
		if($mailqueue->getacl("") == ""){
			$mailqueue->set_acl_base($ui->dn);
		}
		session::set('mailqueue',$mailqueue);
	}
	$mailqueue = session::get('mailqueue');

	/* Execute formular */
	$mailqueue->save_object();
	$display= $mailqueue->execute ();
	$display.= "<input type=\"hidden\" name=\"ignore\">\n";

	/* Store changes  in session */
	session::set('mailqueue',$mailqueue);
}
?>

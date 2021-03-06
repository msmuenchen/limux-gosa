<?php
/*
 * This code is part of GOsa (http://www.gosa-project.org)
 * Copyright (C) 2003-2008 GONICUS GmbH
 *
 * ID: $$Id$$
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

class passwordMethodsmd5 extends passwordMethod
{
  function passwordMethodsmd5($config)
  {
  }

  function is_available()
  {
    if ((!function_exists('md5'))){
      return false;	
    }else{
      return true;
    }
  }

  function generate_hash($pwd)
  {
    mt_srand(microtime()* 10000000);
    $salt0= substr(pack("h*", md5(mt_rand())), 0, 8);
    $salt = substr(pack("H*", md5($salt0 . $pwd)), 0, 4);
    $hash = "{SMD5}".base64_encode(pack("H*",md5($pwd . $salt)) . $salt);
    return $hash;       
  }

  function get_hash_name()
  {
    return "smd5";
  }

}

// vim:tabstop=2:expandtab:shiftwidth=2:filetype=php:syntax:ruler:
?>

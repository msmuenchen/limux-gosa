<?php
/*
 * This code is part of GOsa (http://www.gosa-project.org)
 * Copyright (C) 2003-2008 GONICUS GmbH
 *
 * ID: $$Id: class_plugin.inc 13896 2009-07-07 07:06:37Z hickert $$
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

class listingSortIterator implements Iterator {
  private $data;

  /* strcoll wrapper that will sort underscores to the end */
  public static function sort_underscores($a, $b) {
    if ((substr($a, 0, 1)) == '_' && (substr($b, 0, 1) == '_')) {
      return listingSortIterator::sort_underscores(substr($a, 1), substr($b, 1));
    }
    elseif (substr($a, 0, 1) == '_') {
      return 1;
    }
    elseif (substr($b, 0, 1) == '_') {
      return -1;
    }
    else {
      return strcoll($a, $b);
    }
  }

  public function __construct($data, $direction, $attribute, $type= "string") {
    global $_sortAttribute;
    global $_sortType;
    $_sortAttribute= explode(',', $attribute);
    $_sortType= explode(',', $type);

    // Inline function to 
    function attrSort($ao, $bo) {
      global $_sortAttribute;
      global $_sortType;

      // Extract values from ao and bo

      $sorted = 0;
      for( $i=0; $i < min(count( $_sortAttribute ), count( $_sortType )); $i++ ) {

        $a= $b= "";
        if (isset($ao[$_sortAttribute[$i]])) {
          $a= $ao[$_sortAttribute[$i]];
          if (is_array($a)) {
            $a= $a[0];
          }
        }
        if (isset($bo[$_sortAttribute[$i]])) {
          $b= $bo[$_sortAttribute[$i]];
          if (is_array($b)) {
            $b= $b[0];
          }
        }
  
        // Take a look at the several types
        switch ($_sortType[$i]) {
          case 'string':
            $sorted = listingSortIterator::sort_underscores($a, $b);
            break;
  
          case 'integer':
            $sorted = $b - $a;
            break;
  
          case 'date':
            if ($a == "") {
              $a= "31.12.0000";
            }
            if ($b == "") {
              $b= "31.12.0000";
            }
            list($d, $m, $y)= explode('.', $a);
            $a= (int)sprintf("%04d%02d%02d", $y, $m, $d);
            list($d, $m, $y)= explode('.', $b);
            $b= (int)sprintf("%04d%02d%02d", $y, $m, $d);
            $sorted = $b - $a;
            break;
  
          // Sort for string by default
          default:
            $sorted = strcoll($a, $b);
            break;
        }
  
        if( $sorted !== 0 )
          break;
      }

      return $sorted;
    }

    // Sort for attribute
    if ($attribute != "") {
      uasort($data, "attrSort");
    }

    // Invert if direction is set
    if ($direction) {
      $this->data= array_reverse($data, true);
    } else {
      $this->data= $data;
    }
  }

  function rewind() {
    return reset($this->data);
  }

  function current() {
    return current($this->data);
  }

  function key() {
    return key($this->data);
  }

  function next() {
    return next($this->data);
  }

  function valid() {
    return key($this->data) !== null;
  }
}

?>

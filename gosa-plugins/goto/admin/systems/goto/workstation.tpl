<h3>{t}Properties{/t}</h3>
<table summary="{t}Properties{/t}" style="width:100%;">
 <tr>
  <td style='width:50%; '>

   <table summary="{t}Generic settings{/t}">
    <tr>
{if $cn eq 'wdefault'}
     <td colspan=2>{t}Workstation template{/t}</td>
{else}
     <td><LABEL for="cn">{t}Workstation name{/t}</LABEL>{$must}</td>
     <td>
{render acl=$cnACL}
      <input type='text' name="cn" id="cn" size=18 maxlength=60 value="{$cn}">
{/render}
     </td>
{/if}
    </tr>
    <tr>
     <td><LABEL for="description">{t}Description{/t}</LABEL></td>
     <td>
{render acl=$descriptionACL}
      <input type='text' name="description" id="description" size=18 maxlength=60 value="{$description}">
{/render}
     </td>
    </tr>
    <tr>
     <td><LABEL for="ghInventoryNumber">{t}Inventory number{/t}</LABEL></td>
     <td>
{render acl=$descriptionACL}
      <input type='text' name="ghInventoryNumber" id="ghInventoryNumber" size=18 maxlength=60 value="{$ghInventoryNumber}">
{/render}
     </td>
    </tr>

    <tr>
     <td><LABEL for="cn">{t}Location{/t}</LABEL></td>
     <td>
{render acl=$lACL}
      <input type='text' name="l" id="l" size=18 maxlength=60 value="{$l}">
{/render}
     </td>
    </tr>
    <tr>
     <td><LABEL for="base">{t}Base{/t}</LABEL>{$must}</td>
     <td>
<style type="text/css">
#wrapper-base .treeList { max-width:600px; }
</style>
<div id="wrapper-base">
{render acl=$baseACL}
       {$base}
{/render}
</div>
     </td>
    </tr>
	  <tr>
	   <td><LABEL for="ogroup">{t}Object group{/t}</LABEL></td>
	   <td>
       <select name="ogroup" title="{t}Select object group{/t}" size="1" style="width: 250px;">
           <option value='none'>{t}none{/t}</option>
           {html_options values=$OgroupKeys output=$ogroups selected=$ogroup}
       </select>
	   </td>
	  </tr>
    <tr>
    <td><LABEL for="comments">{t}Comment{/t}</LABEL></td>
    <td>
{render acl=$goCommentACL}
    <textarea rows=6 cols=45 id="goComment" name="goComment">{$goComment}</textarea>

{/render}
    </td>
    </tr>
   </table>

{if $host_key}
   <hr>
   {$host_key}
{/if}
  </td>
  <td class='left-border'>

   <table summary="{t}Terminal server settings{/t}">
    <tr>
     <td>{t}Mode{/t}</td>
     <td>
{render acl=$gotoModeACL}
      <select name="gotoMode" title="{t}Select terminal mode{/t}" size=1>
       {html_options options=$modes selected=$gotoMode_select}
      </select>
{/render}
     </td>
    </tr>
    <tr>
     <td><LABEL for="gotoSyslogServer">{t}Syslog server{/t}</LABEL></td>
     <td>
{render acl=$gotoSyslogServerACL}
      <select id="gotoSyslogServer" name="gotoSyslogServer" title="{t}Choose server to use for logging{/t}" size=1>
       {html_options options=$syslogservers selected=$gotoSyslogServer_select}
      </select>
{/render}
     </td>
    </tr>
   </table>

   <hr>

    {if $member_of_ogroup}
    {render acl=$gotoNtpServerACL}
            <input type="checkbox" value="1" name="inheritTimeServer"
                {if $inheritTimeServer} checked {/if}
                onClick="javascript:
                        changeState('gotoNtpServerSelected');
                        changeState('gotoNtpServers');
                        changeState('addNtpServer');
                        changeState('delNtpServer');">{t}Inherit time server attributes{/t}
                        <br><br>
    {/render}
    {else}
      <input disabled type='checkbox' name='option_disabled'>{t}Inherit time server attributes{/t}<br><br>
    {/if}
         <LABEL for="gotoNtpServerSelected">{t}NTP server{/t}</LABEL>
         <br>
    {render acl=$gotoNtpServerACL}
          <select name="gotoNtpServerSelected[]" id="gotoNtpServerSelected" multiple size=5 style="width:100%;"
                title="{t}Choose server to use for synchronizing time{/t}" {if $inheritTimeServer} disabled {/if}>
           {html_options options=$gotoNtpServer_select}
          </select>
    {/render}
         <br>
    {render acl=$gotoNtpServerACL}
          <select name="gotoNtpServers" id="gotoNtpServers" {if $inheritTimeServer} disabled {/if}  size=1>
           {html_options options=$gotoNtpServers}
          </select>
    {/render}
    {render acl=$gotoNtpServerACL}
            <button type='submit' name='addNtpServer' id="addNtpServer"
             {if $inheritTimeServer} disabled {/if}>{msgPool type=addButton}</button>
    {/render}
    {render acl=$gotoNtpServerACL}
            <button type='submit' name='delNtpServer' id="delNtpServer"
             {if $inheritTimeServer} disabled {/if}>{msgPool type=delButton}</button>
    {/render}

  </td>
 </tr>
</table>

{if $cn neq 'wdefault'}
<hr>

{$netconfig}
{/if}
<hr>

{if $fai_activated}
  <h3>{t}Action{/t}</h3>
<table width="100%">
<tr>
<td style="width:50%">
  {render acl=$FAIstateACL}
     <select size="1" name="saction" title="{t}Select action to execute for this terminal{/t}">
      <option>&nbsp;</option>
      {html_options options=$actions}
     </select>
  {/render}
  {if $currently_installing}
    {render acl=r}
       <button type='submit' name='action'>{t}Execute{/t}</button>
    {/render}
    {else}
    {render acl=$FAIstateACL}
       <button type='submit' name='action'>{t}Execute{/t}</button>
    {/render}
  {/if}
</td>
<td style="width:50%" class="left-border">
{if $member_of_ogroup}
   <button type='submit' name='inheritAll'>{t}Inherit all values from group{/t}</button>
{/if}
</td>
</tr>
</table>
{/if}



<input type="hidden" name="workgeneric_posted" value="1">
{if $cn eq 'wdefault'}

<!-- Place cursor -->
  <script language="JavaScript" type="text/javascript">
    <!-- // First input field on page
    focus_field('l');
    -->
  </script>
{else}
  <script language="JavaScript" type="text/javascript">
    <!-- // First input field on page
    focus_field('cn');
    -->
  </script>
{/if}


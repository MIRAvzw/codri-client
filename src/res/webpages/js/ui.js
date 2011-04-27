/*
 Messaging
 */

function showNotice(text)
{
    var element = $('<div id="newNotice" title="Notice">' + text + '</div>');
    element.dialog({
		show: "drop",
		hide: "drop",
		draggable: false,
		resizable: false,
		position: "left top",
		minHeight: 50
	}).prev().addClass('ui-state-highlight');
	setTimeout(function() {
            element.dialog("close")
        }, 3500);
}
application.notice.connect(showNotice);

function showAlert(text)
{
    var element = $('<div id="newAlert" title="Alert!">' + text + '</div>');
    element.dialog({
		show: "drop",
		hide: "drop",
		draggable: false,
		resizable: false,
		position: "left top",
		minHeight: 50
	}).prev().addClass('ui-state-error');
	setTimeout(function() {
            element.dialog("close")
        }, 3500);
}
application.alert.connect(showAlert);


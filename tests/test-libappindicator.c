
#include <glib.h>
#include <glib-object.h>

#include <libappindicator/app-indicator.h>

void
test_libappindicator_prop_signals_status_helper (AppIndicator * ci, gchar * status, gboolean * signalactivated)
{
	*signalactivated = TRUE;
	return;
}

void
test_libappindicator_prop_signals_helper (AppIndicator * ci, gboolean * signalactivated)
{
	*signalactivated = TRUE;
	return;
}

void
test_libappindicator_prop_signals (void)
{
	AppIndicator * ci = APP_INDICATOR(g_object_new(APP_INDICATOR_TYPE, NULL));
	g_assert(ci != NULL);

	gboolean signaled = FALSE;
	gulong handlerid;

	handlerid = 0;
	handlerid = g_signal_connect(G_OBJECT(ci), "new-icon", G_CALLBACK(test_libappindicator_prop_signals_helper), &signaled);
	g_assert(handlerid != 0);

	handlerid = 0;
	handlerid = g_signal_connect(G_OBJECT(ci), "new-attention-icon", G_CALLBACK(test_libappindicator_prop_signals_helper), &signaled);
	g_assert(handlerid != 0);

	handlerid = 0;
	handlerid = g_signal_connect(G_OBJECT(ci), "new-status", G_CALLBACK(test_libappindicator_prop_signals_status_helper), &signaled);
	g_assert(handlerid != 0);


	signaled = FALSE;
	app_indicator_set_icon(ci, "bob");
	g_assert(signaled);

	signaled = FALSE;
	app_indicator_set_icon(ci, "bob");
	g_assert(!signaled);

	signaled = FALSE;
	app_indicator_set_icon(ci, "al");
	g_assert(signaled);


	signaled = FALSE;
	app_indicator_set_attention_icon(ci, "bob");
	g_assert(signaled);

	signaled = FALSE;
	app_indicator_set_attention_icon(ci, "bob");
	g_assert(!signaled);

	signaled = FALSE;
	app_indicator_set_attention_icon(ci, "al");
	g_assert(signaled);


	signaled = FALSE;
	app_indicator_set_status(ci, APP_INDICATOR_STATUS_PASSIVE);
	g_assert(!signaled);

	signaled = FALSE;
	app_indicator_set_status(ci, APP_INDICATOR_STATUS_ACTIVE);
	g_assert(signaled);

	signaled = FALSE;
	app_indicator_set_status(ci, APP_INDICATOR_STATUS_ACTIVE);
	g_assert(!signaled);

	signaled = FALSE;
	app_indicator_set_status(ci, APP_INDICATOR_STATUS_ATTENTION);
	g_assert(signaled);

	return;
}

void
test_libappindicator_init_set_props (void)
{
	AppIndicator * ci = APP_INDICATOR(g_object_new(APP_INDICATOR_TYPE, NULL));
	g_assert(ci != NULL);

	app_indicator_set_id(ci, "my-id");
	app_indicator_set_category(ci, APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
	app_indicator_set_status(ci, APP_INDICATOR_STATUS_ACTIVE);
	app_indicator_set_icon(ci, "my-name");
	app_indicator_set_attention_icon(ci, "my-attention-name");

	g_assert(!g_strcmp0("my-id", app_indicator_get_id(ci)));
	g_assert(!g_strcmp0("my-name", app_indicator_get_icon(ci)));
	g_assert(!g_strcmp0("my-attention-name", app_indicator_get_attention_icon(ci)));
	g_assert(app_indicator_get_status(ci) == APP_INDICATOR_STATUS_ACTIVE);
	g_assert(app_indicator_get_category(ci) == APP_INDICATOR_CATEGORY_APPLICATION_STATUS);

	g_object_unref(G_OBJECT(ci));
	return;
}

void
test_libappindicator_init_with_props (void)
{
	AppIndicator * ci = APP_INDICATOR(g_object_new(APP_INDICATOR_TYPE, 
	                                                     "id", "my-id",
	                                                     "category-enum", APP_INDICATOR_CATEGORY_APPLICATION_STATUS,
	                                                     "status-enum", APP_INDICATOR_STATUS_ACTIVE,
	                                                     "icon-name", "my-name",
	                                                     "attention-icon-name", "my-attention-name",
	                                                     NULL));
	g_assert(ci != NULL);

	g_assert(!g_strcmp0("my-id", app_indicator_get_id(ci)));
	g_assert(!g_strcmp0("my-name", app_indicator_get_icon(ci)));
	g_assert(!g_strcmp0("my-attention-name", app_indicator_get_attention_icon(ci)));
	g_assert(app_indicator_get_status(ci) == APP_INDICATOR_STATUS_ACTIVE);
	g_assert(app_indicator_get_category(ci) == APP_INDICATOR_CATEGORY_APPLICATION_STATUS);

	g_object_unref(G_OBJECT(ci));
	return;
}

void
test_libappindicator_init (void)
{
	AppIndicator * ci = APP_INDICATOR(g_object_new(APP_INDICATOR_TYPE, NULL));
	g_assert(ci != NULL);
	g_object_unref(G_OBJECT(ci));
	return;
}

void
test_libappindicator_props_suite (void)
{
	g_test_add_func ("/indicator-application/libappindicator/init",            test_libappindicator_init);
	g_test_add_func ("/indicator-application/libappindicator/init_props",      test_libappindicator_init_with_props);
	g_test_add_func ("/indicator-application/libappindicator/init_set_props",  test_libappindicator_init_set_props);
	g_test_add_func ("/indicator-application/libappindicator/prop_signals",    test_libappindicator_prop_signals);

	return;
}

gint
main (gint argc, gchar * argv[])
{
	g_type_init();
	g_test_init(&argc, &argv, NULL);

	/* Test suites */
	test_libappindicator_props_suite();


	return g_test_run ();
}
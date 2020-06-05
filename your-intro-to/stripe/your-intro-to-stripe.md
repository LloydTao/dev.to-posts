## Your Intro to Stripe (Django)

### Introduction

Stripe is an online payments processor.

It's incredible useful for almost any internet commerce; from online stores to subscriptions, and from user-driven marketplaces to crowdfunding.

This guide will briefly overview Stripe and its API, and give examples on how to integrate it with Django.

*If you're using a different framework, it should be easily adaptable!*

### Features

Stripe is **elegant**. It abstracts most of the payments process. You don't need to worry about passing card details around and processing it yourself.

Stripe is **robust**. It can send dummy payments with test cards before completing a purchase flow.

Stripe is **secure**. AES-256 encryption is built in, with decryption keys stored separately.

Stripe is **compliant**. This includes PCI, PSD2, SCA and SSAE18/SOC certifications.

![Stripe Compliance Certifications](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/000-Stripe-Compliant.png)

### Fees

Stripe **Payments** charge 1.4% + 20p for European cards and 2.9% + 20p for non-European cards.

Stripe **Billing**, used for recurring payments, charges 0.5%.

### Extensions

Stripe has a host of additional features:

- Stripe **Connect** - dedicated dashboard for sellers on your marketplace, with a monthly fee per account.

- Stripe **Radar** -  machine learning fraud protection.

- Stripe **Sigma** - SQL-powered business reports, with dozens of templates.

- Stripe **Atlas** - launch a start-up (LLC, bank account, stock issuing) for a one-time fee.

We'll be taking advantage of [Stripe Checkout](https://stripe.com/docs/payments/checkout) for quick and compliant integration.

## Setting Up

### Overview

Our tasks at hand are essentially:

1. Create a Stripe account, and grab your API keys.

2. Install the Stripe API for the backend (Python: `$ pip install stripe`).

3. Add Stripe to the frontend (we're using `checkout.js`).

4. We're done! View processed payments on your Stripe account.

### Creating a Stripe Account

Head to https://dashboard.stripe.com/register to create an account.

![Registering a Stripe Account](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/001-Stripe-Account.png)

Remember to verify your account.

![Verifying a Stripe Account](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/002-Stripe-Verify.png)

Now, grab your API keys. You'll need both.

![Getting a Stripe API Key](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/003-Stripe-Key.png)

### Installing the Stripe API

Let's set up the backend. This is where the private API key will live.

**Project Setup**

Make sure you've set up your project, virtual environment and requirements. [Here's a Django guide](https://dev.to/tao/your-intro-to-django-2020-3a01).

Add Stripe to your `requirements.txt` for pip. You'll probably want the latest version.

![Adding Stripe to Requirements](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/004-Django-Requirements.png)

Install your packages with `pip install -r requirements.txt`.

**Stripe Setup**

In the settings, make sure you've added Stripe to your `INSTALLED_APPS` and defined the keys.

```python
...

INSTALLED_APPS = [
    ...
    'stripe',
]

...

STRIPE_PUBLISHABLE_KEY = 'pk_test_notmykeynotmykeynotmykeynotmykeynotmykeynotmykeynotmykey'

STRIPE_SECRET_KEY = 'sk_test_notmykeynotmykeynotmykeynotmykeynotmykeynotmykeynotmykey'
```

Once you've set up your project, import `stripe` and define `stripe.api_key` in your views.

```python
import stripe

from django.conf import settings
from django.shortcuts import render

stripe.api_key = settings.STRIPE_SECRET_KEY


class ...
```

We can now get started with some views and templates!

### Adding Stripe to the Frontend

Using Stripe Checkout, we can create a payment form (and handle it) incredibly quickly.

**Product Page**

We'll make a very simple view, with our API key added to the context.

```python
class HomeView(TemplateView):
    template_name = 'index.html'

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        context['key'] = settings.STRIPE_PUBLISHABLE_KEY
        return context
```

Our template will be include a form, as well as a script based on `checkout.js`.

```html
<h1>Purchase hat:</h1>
<form action="{% url 'payments-charge' %}" method="POST">
  {% csrf_token %}
  <script src="https://checkout.stripe.com/checkout.js" class="stripe-button"
          data-key="{{ key }}"
          data-description="You are purchasing: Hat."
          data-amount="100"
          data-currency="GBP"
          data-locale="auto">
  </script>
</form>
```
Stripe will validate the payment form. The result looks like:

![Example Stripe Form](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/002-Stripe-Form.png)

**Payment View**

You'll need a view that uses `stripe.Charge.create()`.

You'll notice that the values are hard-coded. You need to enforce them server-side, otherwise the client can just edit the values in the Stripe form.

```python
class ChargeView(TemplateView):

    def post(self, request):
        charge = stripe.Charge.create(
            amount = 100,
            currency = 'gbp',
            description = 'Hat purchase.',
            source=request.POST['stripeToken']
        )
        return HttpResponse('charge.html')
```

As for the template, it doesn't need anything. All functionality is handled in the `post`.

```html
<p>Thank you for your payment!</p>
```

You'll likely want to pass some context data in order to personalise it.

**Demo**

We can try out our form with a [test card](https://stripe.com/docs/testing#cards).

![Stripe Payment Demo](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/005-Stripe-Payment.png)

We can now see the payment on the dashboard.

![Stripe Dashboard Demo](https://raw.githubusercontent.com/LloydTao/dev.to-posts/master/your-intro-to/stripe/006-Stripe-Dashboard.png)

Super easy, right? You can now begin to explore the big, wide world of internet commerce!

## Summary

### What We Covered

In this post, we had a look at:

- Creating a Stripe account.

- Getting our API keys.

- Adding Stripe to our Django backend.

- Creating views and templates for our frontend.

- Handling the post request using `stripe.Charge.create()`.

- Viewing payments on the dashboard.

### What We Missed

There's a whole bunch of stuff to do after payment.

- How do I get the money? [Receive payouts](https://stripe.com/docs/payouts).

- How do I react to a payment? [Handle webhook events](https://stripe.com/docs/payments/handling-payment-events).

- How do I send receipts? [Send email receipts](https://stripe.com/docs/receipts).

- A payment was declined. [Deal with declines](https://stripe.com/docs/declines).

- My customer wants a refund. [Issue refunds](https://stripe.com/docs/refunds).

- What about fraudulent payments? [Manage disputes and fraud](https://stripe.com/docs/disputes).

As well as the pages above, there's also API docs, such as the [API: Refunds](https://stripe.com/docs/api/refunds) page.

### Further Reading

Payments are tricky business, and you don't want to head in the wrong way.

- Check out the [dj-stripe](https://pypi.org/project/dj-stripe/) package, and its [Django + Stripe Made Easy](https://dj-stripe.readthedocs.io/en/stable/) docs.

- *Also, consider some [Reddit opinions](https://www.reddit.com/r/django/comments/gt21py/stripe_with_django_are_you_using_just_stripe_or/) on using `dj-stripe` over the Stripe API*.

- Check out [Create a Subscription SaaS Application with Django and Stripe](https://www.saaspegasus.com/guides/django-stripe-integrate/#upcoming-working-with-subscriptions-in-your-django-application) by *SaaS Pegasus*.

- Check out [another brilliant post](https://mycodestories.com/blog/stripe_django_payments/) on using Django with Stripe.

The Django subreddit ([r/django](https://www.reddit.com/r/django/)) is an awesome, active and high-quality community.

---

Hey, guys! Thank you for reading. I hope that you enjoyed this.

Keep up to date with me:

- DEV: https://dev.to/tao/
- Twitter: https://twitter.com/LloydTao
- GitHub: https://github.com/LloydTao
- LinkedIn: https://www.linkedin.com/in/LloydTao/

Catch you around!

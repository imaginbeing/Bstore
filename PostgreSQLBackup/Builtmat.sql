PGDMP     !    3                {            Buildmat    10.18    10.18 W    z           0    0    ENCODING    ENCODING        SET client_encoding = 'UTF8';
                       false            {           0    0 
   STDSTRINGS 
   STDSTRINGS     (   SET standard_conforming_strings = 'on';
                       false            |           0    0 
   SEARCHPATH 
   SEARCHPATH     8   SELECT pg_catalog.set_config('search_path', '', false);
                       false            }           1262    50175    Buildmat    DATABASE     �   CREATE DATABASE "Buildmat" WITH TEMPLATE = template0 ENCODING = 'UTF8' LC_COLLATE = 'English_United States.1252' LC_CTYPE = 'English_United States.1252';
    DROP DATABASE "Buildmat";
             postgres    false                        2615    2200    public    SCHEMA        CREATE SCHEMA public;
    DROP SCHEMA public;
             postgres    false            ~           0    0    SCHEMA public    COMMENT     6   COMMENT ON SCHEMA public IS 'standard public schema';
                  postgres    false    3                        3079    12924    plpgsql 	   EXTENSION     ?   CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;
    DROP EXTENSION plpgsql;
                  false                       0    0    EXTENSION plpgsql    COMMENT     @   COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';
                       false    1            �            1259    50300    cart    TABLE     �   CREATE TABLE public.cart (
    id integer NOT NULL,
    client_id integer NOT NULL,
    product_id integer NOT NULL,
    amount integer NOT NULL
);
    DROP TABLE public.cart;
       public         postgres    false    3            �            1259    50298    cart_id_seq    SEQUENCE     �   ALTER TABLE public.cart ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.cart_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);
            public       postgres    false    3    217            �            1259    50185    catalog    TABLE     c   CREATE TABLE public.catalog (
    id integer NOT NULL,
    name character varying(128) NOT NULL
);
    DROP TABLE public.catalog;
       public         postgres    false    3            �            1259    50183    catalog_id_seq    SEQUENCE     �   ALTER TABLE public.catalog ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.catalog_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);
            public       postgres    false    3    199            �            1259    50204    category    TABLE     �   CREATE TABLE public.category (
    id integer NOT NULL,
    subcatalog_id integer DEFAULT 1 NOT NULL,
    name character varying(128) NOT NULL
);
    DROP TABLE public.category;
       public         postgres    false    3            �            1259    50202    category_id_seq    SEQUENCE     �   ALTER TABLE public.category ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.category_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);
            public       postgres    false    3    203            �            1259    50178    clients    TABLE     �   CREATE TABLE public.clients (
    id integer NOT NULL,
    login character varying(16) NOT NULL,
    password character varying(16) NOT NULL,
    name character varying(128),
    admin boolean DEFAULT false NOT NULL
);
    DROP TABLE public.clients;
       public         postgres    false    3            �            1259    50176    clients_id_seq    SEQUENCE     �   ALTER TABLE public.clients ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.clients_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);
            public       postgres    false    3    197            �            1259    50251    feature    TABLE     c   CREATE TABLE public.feature (
    id integer NOT NULL,
    name character varying(128) NOT NULL
);
    DROP TABLE public.feature;
       public         postgres    false    3            �            1259    50249    feature_id_seq    SEQUENCE     �   ALTER TABLE public.feature ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.feature_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);
            public       postgres    false    3    209            �            1259    50356    history    TABLE     z   CREATE TABLE public.history (
    id integer NOT NULL,
    client_id integer NOT NULL,
    product_id integer NOT NULL
);
    DROP TABLE public.history;
       public         postgres    false    3            �            1259    50354    history_id_seq    SEQUENCE     �   ALTER TABLE public.history ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.history_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);
            public       postgres    false    221    3            �            1259    50225    product    TABLE     #  CREATE TABLE public.product (
    id integer NOT NULL,
    provider_id integer NOT NULL,
    category_id integer DEFAULT 1 NOT NULL,
    name character varying(128) NOT NULL,
    description character varying(8192),
    purpose character varying(128) NOT NULL,
    price integer NOT NULL
);
    DROP TABLE public.product;
       public         postgres    false    3            �            1259    50258    product_feature    TABLE     �   CREATE TABLE public.product_feature (
    id integer NOT NULL,
    product_id integer NOT NULL,
    feature_id integer NOT NULL,
    description character varying(128) NOT NULL
);
 #   DROP TABLE public.product_feature;
       public         postgres    false    3            �            1259    50256    product_feature_id_seq    SEQUENCE     �   ALTER TABLE public.product_feature ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.product_feature_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);
            public       postgres    false    3    211            �            1259    50223    product_id_seq    SEQUENCE     �   ALTER TABLE public.product ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.product_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);
            public       postgres    false    207    3            �            1259    50218    provider    TABLE     �   CREATE TABLE public.provider (
    id integer NOT NULL,
    login character varying(16) NOT NULL,
    password character varying(16) NOT NULL,
    name character varying(128)
);
    DROP TABLE public.provider;
       public         postgres    false    3            �            1259    50216    provider_id_seq    SEQUENCE     �   ALTER TABLE public.provider ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.provider_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);
            public       postgres    false    3    205            �            1259    50317    review    TABLE     �   CREATE TABLE public.review (
    id integer NOT NULL,
    client_id integer NOT NULL,
    product_id integer NOT NULL,
    rate integer NOT NULL,
    review character varying(4096)
);
    DROP TABLE public.review;
       public         postgres    false    3            �            1259    50315    review_id_seq    SEQUENCE     �   ALTER TABLE public.review ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.review_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);
            public       postgres    false    219    3            �            1259    50288    storage    TABLE     �   CREATE TABLE public.storage (
    id integer NOT NULL,
    product_id integer NOT NULL,
    amount integer NOT NULL,
    last_delivery date NOT NULL
);
    DROP TABLE public.storage;
       public         postgres    false    3            �            1259    50286    storage_id_seq    SEQUENCE     �   ALTER TABLE public.storage ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.storage_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);
            public       postgres    false    215    3            �            1259    50192 
   subcatalog    TABLE     �   CREATE TABLE public.subcatalog (
    id integer NOT NULL,
    catalog_id integer DEFAULT 1 NOT NULL,
    name character varying(128) NOT NULL
);
    DROP TABLE public.subcatalog;
       public         postgres    false    3            �            1259    50190    subcatalog_id_seq    SEQUENCE     �   ALTER TABLE public.subcatalog ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.subcatalog_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);
            public       postgres    false    3    201            �            1259    50275    supply    TABLE     �   CREATE TABLE public.supply (
    id integer NOT NULL,
    product_id integer NOT NULL,
    amount integer NOT NULL,
    approved boolean DEFAULT false NOT NULL,
    request_date date NOT NULL,
    approve_date date
);
    DROP TABLE public.supply;
       public         postgres    false    3            �            1259    50273    supply_id_seq    SEQUENCE     �   ALTER TABLE public.supply ALTER COLUMN id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.supply_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);
            public       postgres    false    213    3            s          0    50300    cart 
   TABLE DATA               A   COPY public.cart (id, client_id, product_id, amount) FROM stdin;
    public       postgres    false    217   3`       a          0    50185    catalog 
   TABLE DATA               +   COPY public.catalog (id, name) FROM stdin;
    public       postgres    false    199   \`       e          0    50204    category 
   TABLE DATA               ;   COPY public.category (id, subcatalog_id, name) FROM stdin;
    public       postgres    false    203   ,a       _          0    50178    clients 
   TABLE DATA               C   COPY public.clients (id, login, password, name, admin) FROM stdin;
    public       postgres    false    197   �d       k          0    50251    feature 
   TABLE DATA               +   COPY public.feature (id, name) FROM stdin;
    public       postgres    false    209   )e       w          0    50356    history 
   TABLE DATA               <   COPY public.history (id, client_id, product_id) FROM stdin;
    public       postgres    false    221   Ig       i          0    50225    product 
   TABLE DATA               b   COPY public.product (id, provider_id, category_id, name, description, purpose, price) FROM stdin;
    public       postgres    false    207   �g       m          0    50258    product_feature 
   TABLE DATA               R   COPY public.product_feature (id, product_id, feature_id, description) FROM stdin;
    public       postgres    false    211   �       g          0    50218    provider 
   TABLE DATA               =   COPY public.provider (id, login, password, name) FROM stdin;
    public       postgres    false    205   �       u          0    50317    review 
   TABLE DATA               I   COPY public.review (id, client_id, product_id, rate, review) FROM stdin;
    public       postgres    false    219   ��       q          0    50288    storage 
   TABLE DATA               H   COPY public.storage (id, product_id, amount, last_delivery) FROM stdin;
    public       postgres    false    215   2�       c          0    50192 
   subcatalog 
   TABLE DATA               :   COPY public.subcatalog (id, catalog_id, name) FROM stdin;
    public       postgres    false    201   j�       o          0    50275    supply 
   TABLE DATA               ^   COPY public.supply (id, product_id, amount, approved, request_date, approve_date) FROM stdin;
    public       postgres    false    213   �       �           0    0    cart_id_seq    SEQUENCE SET     9   SELECT pg_catalog.setval('public.cart_id_seq', 5, true);
            public       postgres    false    216            �           0    0    catalog_id_seq    SEQUENCE SET     <   SELECT pg_catalog.setval('public.catalog_id_seq', 7, true);
            public       postgres    false    198            �           0    0    category_id_seq    SEQUENCE SET     >   SELECT pg_catalog.setval('public.category_id_seq', 41, true);
            public       postgres    false    202            �           0    0    clients_id_seq    SEQUENCE SET     <   SELECT pg_catalog.setval('public.clients_id_seq', 6, true);
            public       postgres    false    196            �           0    0    feature_id_seq    SEQUENCE SET     =   SELECT pg_catalog.setval('public.feature_id_seq', 39, true);
            public       postgres    false    208            �           0    0    history_id_seq    SEQUENCE SET     =   SELECT pg_catalog.setval('public.history_id_seq', 14, true);
            public       postgres    false    220            �           0    0    product_feature_id_seq    SEQUENCE SET     E   SELECT pg_catalog.setval('public.product_feature_id_seq', 77, true);
            public       postgres    false    210            �           0    0    product_id_seq    SEQUENCE SET     =   SELECT pg_catalog.setval('public.product_id_seq', 18, true);
            public       postgres    false    206            �           0    0    provider_id_seq    SEQUENCE SET     =   SELECT pg_catalog.setval('public.provider_id_seq', 6, true);
            public       postgres    false    204            �           0    0    review_id_seq    SEQUENCE SET     ;   SELECT pg_catalog.setval('public.review_id_seq', 3, true);
            public       postgres    false    218            �           0    0    storage_id_seq    SEQUENCE SET     <   SELECT pg_catalog.setval('public.storage_id_seq', 3, true);
            public       postgres    false    214            �           0    0    subcatalog_id_seq    SEQUENCE SET     @   SELECT pg_catalog.setval('public.subcatalog_id_seq', 51, true);
            public       postgres    false    200            �           0    0    supply_id_seq    SEQUENCE SET     ;   SELECT pg_catalog.setval('public.supply_id_seq', 8, true);
            public       postgres    false    212            �
           2606    50304    cart cart_pkey 
   CONSTRAINT     L   ALTER TABLE ONLY public.cart
    ADD CONSTRAINT cart_pkey PRIMARY KEY (id);
 8   ALTER TABLE ONLY public.cart DROP CONSTRAINT cart_pkey;
       public         postgres    false    217            �
           2606    50189    catalog catalog_pkey 
   CONSTRAINT     R   ALTER TABLE ONLY public.catalog
    ADD CONSTRAINT catalog_pkey PRIMARY KEY (id);
 >   ALTER TABLE ONLY public.catalog DROP CONSTRAINT catalog_pkey;
       public         postgres    false    199            �
           2606    50209    category category_pkey 
   CONSTRAINT     T   ALTER TABLE ONLY public.category
    ADD CONSTRAINT category_pkey PRIMARY KEY (id);
 @   ALTER TABLE ONLY public.category DROP CONSTRAINT category_pkey;
       public         postgres    false    203            �
           2606    50182    clients clients_pkey 
   CONSTRAINT     R   ALTER TABLE ONLY public.clients
    ADD CONSTRAINT clients_pkey PRIMARY KEY (id);
 >   ALTER TABLE ONLY public.clients DROP CONSTRAINT clients_pkey;
       public         postgres    false    197            �
           2606    50255    feature feature_pkey 
   CONSTRAINT     R   ALTER TABLE ONLY public.feature
    ADD CONSTRAINT feature_pkey PRIMARY KEY (id);
 >   ALTER TABLE ONLY public.feature DROP CONSTRAINT feature_pkey;
       public         postgres    false    209            �
           2606    50360    history history_pkey 
   CONSTRAINT     R   ALTER TABLE ONLY public.history
    ADD CONSTRAINT history_pkey PRIMARY KEY (id);
 >   ALTER TABLE ONLY public.history DROP CONSTRAINT history_pkey;
       public         postgres    false    221            �
           2606    50262 $   product_feature product_feature_pkey 
   CONSTRAINT     b   ALTER TABLE ONLY public.product_feature
    ADD CONSTRAINT product_feature_pkey PRIMARY KEY (id);
 N   ALTER TABLE ONLY public.product_feature DROP CONSTRAINT product_feature_pkey;
       public         postgres    false    211            �
           2606    50233    product product_pkey 
   CONSTRAINT     R   ALTER TABLE ONLY public.product
    ADD CONSTRAINT product_pkey PRIMARY KEY (id);
 >   ALTER TABLE ONLY public.product DROP CONSTRAINT product_pkey;
       public         postgres    false    207            �
           2606    50222    provider provider_pkey 
   CONSTRAINT     T   ALTER TABLE ONLY public.provider
    ADD CONSTRAINT provider_pkey PRIMARY KEY (id);
 @   ALTER TABLE ONLY public.provider DROP CONSTRAINT provider_pkey;
       public         postgres    false    205            �
           2606    50324    review review_pkey 
   CONSTRAINT     P   ALTER TABLE ONLY public.review
    ADD CONSTRAINT review_pkey PRIMARY KEY (id);
 <   ALTER TABLE ONLY public.review DROP CONSTRAINT review_pkey;
       public         postgres    false    219            �
           2606    50292    storage storage_pkey 
   CONSTRAINT     R   ALTER TABLE ONLY public.storage
    ADD CONSTRAINT storage_pkey PRIMARY KEY (id);
 >   ALTER TABLE ONLY public.storage DROP CONSTRAINT storage_pkey;
       public         postgres    false    215            �
           2606    50196    subcatalog subcatalog_pkey 
   CONSTRAINT     X   ALTER TABLE ONLY public.subcatalog
    ADD CONSTRAINT subcatalog_pkey PRIMARY KEY (id);
 D   ALTER TABLE ONLY public.subcatalog DROP CONSTRAINT subcatalog_pkey;
       public         postgres    false    201            �
           2606    50280    supply supply_pkey 
   CONSTRAINT     P   ALTER TABLE ONLY public.supply
    ADD CONSTRAINT supply_pkey PRIMARY KEY (id);
 <   ALTER TABLE ONLY public.supply DROP CONSTRAINT supply_pkey;
       public         postgres    false    213            �
           2606    50197    subcatalog catalog_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.subcatalog
    ADD CONSTRAINT catalog_id FOREIGN KEY (catalog_id) REFERENCES public.catalog(id) ON DELETE SET DEFAULT;
 ?   ALTER TABLE ONLY public.subcatalog DROP CONSTRAINT catalog_id;
       public       postgres    false    201    2752    199            �
           2606    50239    product category_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.product
    ADD CONSTRAINT category_id FOREIGN KEY (category_id) REFERENCES public.category(id) ON DELETE SET DEFAULT;
 =   ALTER TABLE ONLY public.product DROP CONSTRAINT category_id;
       public       postgres    false    2756    207    203            �
           2606    50305    cart client_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.cart
    ADD CONSTRAINT client_id FOREIGN KEY (client_id) REFERENCES public.clients(id) ON DELETE CASCADE;
 8   ALTER TABLE ONLY public.cart DROP CONSTRAINT client_id;
       public       postgres    false    2750    217    197            �
           2606    50325    review client_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.review
    ADD CONSTRAINT client_id FOREIGN KEY (client_id) REFERENCES public.clients(id) ON DELETE CASCADE;
 :   ALTER TABLE ONLY public.review DROP CONSTRAINT client_id;
       public       postgres    false    2750    219    197            �
           2606    50361    history client_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.history
    ADD CONSTRAINT client_id FOREIGN KEY (client_id) REFERENCES public.clients(id) ON DELETE CASCADE;
 ;   ALTER TABLE ONLY public.history DROP CONSTRAINT client_id;
       public       postgres    false    2750    197    221            �
           2606    50268    product_feature feature_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.product_feature
    ADD CONSTRAINT feature_id FOREIGN KEY (feature_id) REFERENCES public.feature(id) ON DELETE CASCADE;
 D   ALTER TABLE ONLY public.product_feature DROP CONSTRAINT feature_id;
       public       postgres    false    211    2762    209            �
           2606    50263    product_feature product_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.product_feature
    ADD CONSTRAINT product_id FOREIGN KEY (product_id) REFERENCES public.product(id) ON DELETE CASCADE;
 D   ALTER TABLE ONLY public.product_feature DROP CONSTRAINT product_id;
       public       postgres    false    2760    211    207            �
           2606    50281    supply product_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.supply
    ADD CONSTRAINT product_id FOREIGN KEY (product_id) REFERENCES public.product(id) ON DELETE CASCADE;
 ;   ALTER TABLE ONLY public.supply DROP CONSTRAINT product_id;
       public       postgres    false    213    2760    207            �
           2606    50293    storage product_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.storage
    ADD CONSTRAINT product_id FOREIGN KEY (product_id) REFERENCES public.product(id) ON DELETE CASCADE;
 <   ALTER TABLE ONLY public.storage DROP CONSTRAINT product_id;
       public       postgres    false    207    215    2760            �
           2606    50310    cart product_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.cart
    ADD CONSTRAINT product_id FOREIGN KEY (product_id) REFERENCES public.product(id) ON DELETE CASCADE;
 9   ALTER TABLE ONLY public.cart DROP CONSTRAINT product_id;
       public       postgres    false    207    217    2760            �
           2606    50330    review product_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.review
    ADD CONSTRAINT product_id FOREIGN KEY (product_id) REFERENCES public.product(id) ON DELETE CASCADE;
 ;   ALTER TABLE ONLY public.review DROP CONSTRAINT product_id;
       public       postgres    false    207    2760    219            �
           2606    50366    history product_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.history
    ADD CONSTRAINT product_id FOREIGN KEY (product_id) REFERENCES public.product(id) ON DELETE CASCADE;
 <   ALTER TABLE ONLY public.history DROP CONSTRAINT product_id;
       public       postgres    false    207    2760    221            �
           2606    50234    product provider_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.product
    ADD CONSTRAINT provider_id FOREIGN KEY (provider_id) REFERENCES public.provider(id) ON DELETE CASCADE;
 =   ALTER TABLE ONLY public.product DROP CONSTRAINT provider_id;
       public       postgres    false    205    207    2758            �
           2606    50210    category subcatalog_id    FK CONSTRAINT     �   ALTER TABLE ONLY public.category
    ADD CONSTRAINT subcatalog_id FOREIGN KEY (subcatalog_id) REFERENCES public.subcatalog(id) ON DELETE SET DEFAULT;
 @   ALTER TABLE ONLY public.category DROP CONSTRAINT subcatalog_id;
       public       postgres    false    201    203    2754            s      x�3�4�4�4�2�4�1z\\\ ��      a   �   x�e�M
�0���)z �=��1��Jp!@HK�5��
on�KJW��|�~���C����/�XxnZ��R�Υ�yr��db�zny'9<)ި�ij��+����@��^N�vڸVx�ꩶ	��D�AE陷���A&
��,�b�4DZs��=X�
�:�u�%^c�,v�o~�d!�]|��99��vs���R�       e   K  x��UKNA\w��� 9��clos�,��a��B"��	R$#Q>�&�<Ќ����(U�gl�B���U����|/�j_J)$��-��'r�r�S�vmL�j eu��yu��;ɤ@t^��g��Nf0;�}.�d61Ij����2���U���Lr�(2��6հ���}�6:���w�D��կ��`_�m�$#�d'Zj�AĳG	1���Wp��������p�e��s�Q�=u��q /_ھI�����}λ�r�$���6�id)7jT��ښ�P�l[IP��$4�(2I��O}"|��b��\�w�r;o߽ٵ8���	s�j��3J�$'�;&m���6J�����F{�˓�!4yפTYBOY�L9�TK�U&��P��/x�6��5���*WƖՇZ>G�X�ǩ�l�ָ�M.m�4!,�P¹�T��Ȍv�T�9Uo����$r�����JHQS��텫>�ZxZ�85��E�U���;jʔ�;�؟���0�|�T�@��ҳI�
8L9N�#��x8PW��u��B�Z���85�י����+���tOS]����N v�˘��֐j�~ݻ�C����J��^j�\�@;�w��	��'K;�9�Y1����Pcd0��,�����y
����=Я�ڃ`�:ulGc'��Z�Up�㜄އC��3����;���P��2��3Ǚ�r���O�]s��p�����JZ�S�]���$�������KE?���M�����朞�G�[ܔ��C1�p�𙫶Ql[�Ϳ�R�pU��,�3Mt�VkE�pR>�S8�ۣ�t�޿���Lp�      _   �   x�U�Q
!E���p�Z�����c��(�3T�i�9PQ?�{9��*�1z��*�1qM��!��(K�H0�-0�2�N�6F+8��5Zwa�R�����.�5?�.��L��.��K�����.ii���K���G8�zi׍�̺>�      k     x�uSKr�P\kN�Nಞ06w�a�&UIV�ğĕ�Rd��fn�X�Bo�MOwϨ��/-l����B�r���`����Fgx��O�=�Dй68~�kT樯�4�G���`r��T/mܵ2H��Vކ���J�-qm�8[5�@�!�}�4M�y4؋ƶr�Z�};��[�-'$�RUaWhWI�A���~sd�|)i/џ�u�`��ZA;�}VC��yGU�U�Ag�� F��3ޯt:]Щ�Ta�va�a4l8������gS�nV���ٶ�w��4�y�m7fp�,�Z����vn�^������n�D��61Xc��1�H�+l��h��
�� ���;���m���Υ�$��nJv쫄�%͓,=4�7�[�2����`�n�^�ܣO�흸%��K�g�wh:>��nUמ,�U�}?�-`�_ ~G�h�|Q&�>�x0�9܃R��N#�e�l���,D��W�k��俈,}C*'��a��+z��!���|9�&â/      w   C   x���� ����r�@/鿎X�N�BE���$���|*�e���m�H�FBizm�i���A�      i      x��]y�Tו���OHu'UPU��f@�+�&��G��,E^�
�y��60@w��lA�$Q��RQ]�~][K|���B>I���s��2��F�Iwu���r��Yngay���~��8����F��5����Eڍ�[i7�O����I�i���t�NҞ�xl���v�N_�������}���y���s�}�>jƉ��y����'�S�m�1���C���(�g�f,�|�a���uz[v�M��4�a���4��i�4�ƌ���yn�|O�I���拘��ޔ��q�7�ޢ������X@��e[恉��g���|�Lm`�81/4_Kw�	:1Oޡ��ү��-��~t�����6�AD���ai/h{��4L:�:���'�Z��|6:r�(���uƝ\��d"y���.\�$J����V�?�E#2�3k������;�?�:F���$
T���ӗ���_9s�µ+�h�^�r��Ϧ��T�E]��Sf����G/"J�Zlb��g�5SEM��̆��m����^~�I�a�
z�S�r�S\��ݏ�4!иCi��$����Prh~lg����k��^l��<�D�=lbL�h�A%��a�������qĴ�#�^`$"��X���r�+����]�`�yM�I��whx��8⭡9))a��x�~�n�'{�|������<0Ƈ��7����	����ź��Cfk���;��<��|H��c�z�n�DB[��-�W�S�Q�&i���x���]��3L���`a -�ǘ?#N�&����Ү�b�wz��L���H1G�mE"��pz�_Ї��/hN�&,`H 0�� ,�d���M�(����Ō{��P*����cO�F1Żc��u��S�52���a��q��c:Y}4��Y4��>��l���cV	'/Җ���f_hVԇ)�h�k���׆LVc�����$�`?�䀑��>�1�*�Ub#F����f�FY�|�93(��J�9
֒��>1��!03؅ ���Mֆ�w��k�����7Δ�2�Q6��(�����MC7i�L{8��Uq ��]C�q�j@U��9>�l�jwe��Vڒ�&��|�'�Ճ8��"7�9G�f�_��1�
:"���O]��/��?:�۳�V�L QT�++	#�`�]�K���Gi3�Q3�?��t�j���Z�p&�հ�k��q�W��؞}Q�B`v+N��|�ԝ������N�Ѿ���}c�U���[�����#K�S���Y��ch֝Jeh�3����~���x��I�ܝ�M�[�R5����7�?�:��=���,�v�v�`�v�)n�d���i�@�������h��#��Ω~�f�G�]�~��JG1�����͈�y2$�IT���5��I���VW��I$6j�p��_b����x�!����}kׁXG0>��%f5�G�V�&�݀��#�lP1tRkN�6|�k�,?��>�&ҥ��?U�S��WD�����_��Tj�'���B��e͐�/]8k}+r�#�Q��r���vka���e�d�)��L|������W#jw�+�y�����Ϭ3[4x��&+4B2]Δ6��0I�fq5���`
����cd��O����!���y����Ok�N=/��:�E�l���g���2'Y��S��0`Ey���k���%�ҥ���[;d��<ҧ��Λ��!<4��w��O��
��L,��i	�+=������=5
_ׁ.��+��!����Q�U��>�9�4�^
���������"
��V1b�D�Rl�]����O��$&�-ywjyտ�?$��ef��KVi~��۩o�%� +>�[L^�)|�ۇ���,@�;ɇ��K������%E�t<���;�A�5ղ9LϣVr�i���V�y���r�xŬ�i5p(�Rd>��ٮ[���OaK��@7�qC��Mq�����x��C	��њ6汸����A��֣��Pc��󋇭Wx �P|Ş���Y�0��KRc�>�>z��#U���a UJ)x��a�Q|"����F9GC��o!�j�~��Œ���>�r�6�"L"v2i�x+��Qw������-��20�/	��6�$8�<�c�D��󛾁��af�RVz+��+�W���V�y�e�*�C���Dܻ~�b�y�Rw�����D�`�]3��H��=��!�EAJ��3��AT9Ԝ��Pt���'0�k�<��!q>�Hx�z�8�̩�`�D����'����-�;K�*��5�VA��^��2c��hu̘���,"�*���^�kwlG�R�^U�Y�������9���=�.������,�p�Ľ�!����g��Sο%'����M��k�2_�gX�CW��ߌT�քv�:�F6j'h����g�H�D,�tb);�/��t�6t�rO�6�B����p#WP�PS^c0bhg3aa�`�^/��l�Z>�v�ܢ�0�:jѽ0DO��F$��3̹��X4�~��喂bu���y@>� c%'`�[����X�Q�~O8P�K��X���eU�a�����Q��51��K3���r+ B���_瑣�uA��U;��g$$���N����ѹ~ʴ�|�: )o��r�ɑxe=��Z|�ⅆ ���V��h�Q����'��1[*��7�n�����z��-��/8P��UC�y�PȌ��u��ސȇ���R`��4q�.�؊ƅ���93l�,�,�= zY��f[V�#�yB�E����MOcH�,Q������ŽLm����x�pg���u(�[ ]k��`�$.Zs ��15����]C��d'�A(,3�HTe�d�!eԘ3��VE6dYl�UD)�U\Q.��nM�>�3�ij�t]�%<lb���oYq ~P�f�a��/$ۭ;��i.�A�:��0{>��Po�X�(�PF��D�e<t�	��@Q#k Ps�e�iun�^���E�`�+��|^H,�B�/䳑�"���MY��QJ�\� (�y^�!DӉ�Y�w����o��\��.�ˬʱ��W�*�5��U1 rG�I��Ia@�����;�Nj�@�U:�5/Y��Vsl�Y��Ԫ�9B&zu�B�{�R����5@x��$`���%Η�6/�&ꌴ�P^���nު�s	0F������^�m�B3H���� �c�����y&����&��.�d����C ��P������R���4���_&�x0aWݯi���j&>`{��"=ۂ�Y�MU�����*����gI����p�gy����g!:�˃_X9v�P��A��l�a ��l ��[xJ�����#���Q��XmR�I�~K�����㛍����Rlk&י�SL�aW<�x�R����2M��hE���������뫕�^���0pBL�I��M8�@��3�&�?z�ذ^�d�5�ܥ��jC+�����A��ŹZ@��A���
?^:BYb0'�}��)����� ϱ�Ө��
YzF^�`��e���J.���6��<p�K��l��[bh��@����ׄm`U_��9�^ivZ�N���O��N�!�K��j�R���k �!{"�rj����L�.*�-���l��,�b.�&�Z��}hv��E�pj	�2l��v�eck�o���311��w!�0C,��Ґ}�7a:��`�.�jl_���z�L�)�]<n31:��%�Xp�Q8�ޒ�	�`��{�Mn͗-�	O;��K�V��s�\��=.�!���0�Tdp�y;�K�b�r#[k���$k�O�|����r3m�#p> J��y�����"9EsoC��,5���v�������fڦ^Z�
��
 I|{��ۉ_���o�#"A��"�l�S����}��S(KW��_�:&6V�֌�Ҝ.�̚�G��=�F�<��(��4L�j���5g2�wx@�	9��$��^@V�΂۔���=r���t	5_J��Xsn7���v��=�"`"/-䳆�1D7��Df�(��I�Yn�:    �����8n��jٽreĻ�p�{C�$XH:'~����NxpS��)!���C<?���7]�	qF�rȒ	�-�))Ӻ�}%L0sR�B^k�w]RʂW�a@�e�|�}�*��s*�FJ�িBJI�5�d�~.�;ado����V��u��"�M��Nx_9�C�8 W�M�2��P=��@2�o���2@:�U��#����B���w��:K{>mn\PD��{��d\�� ��WZ9`ݏ�s�4~9�\H|fɞ�ٗ�`���J��̡ⵅ�L�p�zυ�8�e�YnjD@��d�#s{�N�R�0v*�j�iM��t����0O���a�)K4������<u�?�
s��e��/���Ql�nx9 eŅ�<�9�����
!��z3��s�E MiC8�j$+�5ݠ�����>ל_��v�P����b1�cVd�k��Y�f_=���a�>���T�Ǒh����	�aI��ݢmS�������Z>�ǧ���� T�i�-��@-{��$�Ŕ0���`�#�S�P������[oOӂ�/��EPZ���*q�1i�+4ˇ����ۮgݖ���7����jwV:��� �|m�Ǽ��i^`�RЈ��5��O�X	��̫�V��,��2�aoO�?X�ͧm:
�mk�|>C�y�D�h�gl�e臐]FlJ��l��Y���
���J��]�zEG��H�i�f.<Tp�B�ѡ6~�-����j�$��<!3�*պ'j{��G�=��:-�3��3�,���/��q����es�c��}TO��:������� G�z�,K��pv_qMI:�"���������#Q����t�f���qvmst+|t_�9�j⊊ɮ�S�AA��tF�4ӻ9z�^� ���{iW���Kј�e��,�*���!3l�A��ё�����BX�R�H�d^����vS���2��[}�j���h��I;�/��1����aq�e�`��jhu�F��PW�P�z�;M������|cX�eȘ ������/�>}x���W�����k�.^;]��?Ν9��w~�|�?OE\���o�#Klq�ڹ�/_�t����]�������_�8S`�T~�'��2�(p^��
�5��M�P�(
q��Za�[d��0X��P�������k�,��ZԞ�	�,�7�%�j[X]X�hu���"�M�ۜM�n5;�%3�����,4�D�P|�~��y�k6�͹��j��β
e���Ul��%đ�X�ڐ�Wӌ�Q�y!��*�:��8Q�K)�઻`O�˧�e.#
; 1�������a���}E�㪂�.g!���Dp^�TS�)�k�l��UZ��0
�7�$�qע������d*x=^�\5<��ٛ4T��>㚢�|n�LvE�iM�ߎ"I�^i�8���r#'j�� �5:g-1,䢅\�s�e�W�p��UI�a#�.F����j�eP\��x��������ks��8_e��vZ�6������;�J}�p
P8�C�R䅅z��9ѱ�5�P8���nm��G��̏�?hh7�f
�XQM�/ႆ4撁��?wY�VՈ ���_V;��]�� �r ^�����Cג���l�!S c�Z�Z�o�6��Âc��ݥ~Y^Kq"��e͹=j+��z�2�]�o���^��H��"c��B�h3*i�����Pmg=�&�Ҋ�* o��G0c^�L]��5	��!���ImP�l$�F¤ha$8��H�H-�\��������]�&�39��{��}�ݺs4�\�H��\,�zz*K�#��7i���[0"	��҂Ԯ�UVO��� �S�׽�� ��F��{�ri2f�ʔ3��ؤn��0�Mv��I��-0��<�nn���]�s>8��0O�M��+���&�����\/=kی�U���r����r��)༩wm�)�z"A��2[���j�� �3�_#��x��+�d���}�0w���MB�-���8\�H���.�7�*��X4���=n��Y�ٺ����R%�o�q�<�cH�p�+9�h�:�M]�r��U�b�Q��Ұ�������]6�/ȴ�=��4i�����PY�g�A�L��UT3֦`����@0��O�^��I�D�#hϐ��=����+�,�ְ����S5�����i��z%��bv�W/�Wֿ	��KzB�w�ϼ���g�-�º,�AԬ5c�Sj�에-��Bw���T$
��I;�,q�����S�k3#w�Z�uu�9~X�)�&�������ҵ����%T7��ϩ9��ӻ�t]�L�²S����=�3�5�����}X�{�5)#_��"A���<���"��> 3l�:w5��>�\a]�C����ܫז=�ʡ�޴�R����ƕ������L�7�s][�Y���-kg5~T�v5"��^��i�5�r�����6��)y�l1gux-��(�u�j�P�N��ϴ_�Ns�3���������puf���̍��srK$��j�H��"�tw��zA�?��W����ޫ���.�w-�A���H�
���~��ȸ�ĝg�8���iܾ�3<��\�b�yXN7 ����Y�Sp7�.����8U�v&���x�0`�
N��N&M�2N�v\E�2Ф��׳`]�{�ZT����%q�U������Ed�+�zQِwB��^>��h/@�S5|�&m;\8}�I$M�o�~��*�,�Ѥ��\��ȝu��<"�R'���Sv+�L0D��Ș�-ApN����5�K� �����]��sz�֚Z-�UYxZSԛ8�T�QQ�������� � `v-w�C8��Bȋ`�1}l��#)����	�4F��eҠ�U�[V`��X->����Ba���[(6�t򩴤-������H^�f��F�q��$(�k��<���E���m�c�����j�K��$TbB+M�K�S��,H�\�ey��#Q.�N#�������J�h���v�h+��C*����P�Y��� J�./7l�^j,aw�]����d�*�p���;i�&ˁUGY`w���#�v�����G�����R�ߚ�����1잾ώ=?�B�4ǉs��'Q�#ZȢ.�9�V��ȱ��F��)�4��D,��5͎`D�G{.� u5bD!�J�Bh�H �Y*�Ƞ�]�u����:�>�plae!�+����)��pA�j��$�ݵ�h���ܕsW�_����sW>�����ߞ�r��T����F[(��b�����w~�|��v*Z���[�O�������Ώ~���������]9������֑v���n�Z��j�u��^9sx�3W�5����o� ���o���Ֆ ��z�i����	�t��$7����Յ��=�O)ɕZ�Y���>A"�*ntرU{ 8?�"~tl�Kkʹ�����k�'݄F��!������&8y�brb�8��Q}uP��7��D�Y�Z��^*1��6�˯V�IIS��U-�Q�t�5~�~��3]��/g�MqO���{l������k�g�q�{K�RB;O�l����9����Aًul;�����Y����ضp�S]Ȫ���:�ރ!YW3���-���lX_�4���8���V|sW��ķ���l���:)N7�e�Ӗޝ~�,����@z�����R�# �7Fǋ5�[�U�wE������J���ك ��;_"��}��M�o�y� 8UU��8+��M�J�*��3[��g�q7^uB�7/��L���\�N�f��(�Y�#m;P�����o�- �����8�/W\����|�7��n/T�f����[+��}\�a5���AW���ݨ����/'�>zx_>�P��wK�~��9Y�&�y��,r����+��-���iNuy�(�.���K,)Eb����D��:�p n��ƃ�5��o���%���C#- �v{zͶ��J¬�B�Ѫ�:̓�XIGi�f*m���]��Ŀ�q_CV�Rt�z�c���*G8��i�����V%'����mKT�x9^���:���6m���+��(��q�<<B�<.�4v��9,k��E)�9�0K d  �EÔ̚'����.hGS�u���꽓e(�� Z�h;fց�˵�7�:/]�J����'��ً�laԶv�����寅t^չ�!m�I��H,�hU,�a�Rm/��O��
�"�6��ҏ�aNG��ȕ�4����b;���fV*9�,+��SمV{{=0��{���]�~������/�j0�敹��i�y��x���I�X��:���f���M5Op�Gi�fG�?�9�f=�kJ�B̍h�]�Ns��	4��N���c��;�����D����v*p�ZD����涼��,����~�!�p몮&q���L�1�V ��Rz�������X��d����y�n�'�Q]��Et}��»JwrY���+��|�����{WZߙ��X6��Xnn�U���aj9F�ic�r�X���)��W P��L��5�����:�L&���x
���$����U�;[s����7�k"�U5��s���.d��L7����鑾�s'%�*�z�f��\�LD�Q��4ɋ6���#��J��)w���F!�5xPԠf�ے�!M
�D��p7��g����G%�8�����)I�P(��8�)0��x�ʫ�nkL��g�ĩ��[;9zХ�q���Y&�*���i����+n[���3d��Y� ����"�؛�ɬ�0��`�$/+�W��h��<6e�_�B��xЋ:�Zn+� �ּ�ٛz�F���Ipw������L�B�z�i��,[��>�n����r�d\�c���򥢳uq[4��p�f��~��
vU� 9�[���3C����l�F��Mж�H���DD1|~���p�Зb��_X����{ƳT�
v5��K�9�~��VN��U�s^G�-oRlW7�,L�E�U4��)3@��anf/����i���([LW1O)���_Jz������{�#�Ͱ��;�|�2���˜��J�2�r�-S�j�AT�C��2eh(�X
b-��5�%����X�5Z�&�n⫀�u. r������RX���ի	\K�0�0�)o���ˤ�r��H�n��6fkh(���g�
�����u:ޭv*��J~G�[�1���_�P���Ԓe��R�*�qd厏?H�DEE�̗ 4U�.�z��̗@Eլ� z�J'R7����qdM�|IR��t�]��íV$�ΰ�'�$�1�oN1��z�G�M�%`Z��xJ��`{�Y���*�!X���,����R\���s�h����lm%����� ^��JJ������m9!^�sr��Nȓhxdط%�[I�����^ޒ�Pn�M��60��߯ػ�1��G��9�]nk_g ~�Uw�>R����u%�,�X=q�#��d�Y�      m   �  x�}UKnG]w��7���f�;\�9�$Gq`�dف� kJJ$e@'辂O�W�g(�A��X���y��M���*,��U��|�����y^�L9*�0���j���M����VT�ܵ���+)���D�:�7y�5Y,<�FS��S]ӹ��w���I�<�O5�8�Zo�Z���B��U���6t����|o�� ��!n8�7�O�axVS�@�>��g�0O�/�9t����q�+� a��s�>�ȗ��X	��S�����ǒ׺�=��5v̦�m����8���-ϤH;Ul{� �p�w�i�W�
�������-��:�f
#\�|��kt�4���ɈR�w�1��Zߢ�U��6��?�� ��H��J`�߅����Cd�QgH%T�j�ĚS��mƖ����&���������Ȉ	-����#w����}o���{:��'�|�W崼��r
\��cFE��)�pB�ҡ�@�����&�̥������`S��|'>I8v�{�ZH�q��� �g,��ۻm��z�`�i�H*/HD�i��� ��.1�5���H���8��>
9~(=�OJ���A{�f� �'�D��->p���u����Z�Փ��.:8U��2�c}�|��`(zwhFv)@/[����s#?C�cc�*QHL���e���^aa너;3�u�7��K��\Gn���R$cѤ�Z?6I)Kؖ�>af$�ar�X\����m&&6M G��~��rb�?0�ޏӐ1�A���p����㜰�" $���+�P�J���w�:���,\3�=?8[I�s�Au�c���j���r�z��cb����Q�AN��;AC��[2�uV�:QQ�4ZWGF�D�t�z@2��k�=���g��3��S�8?hɏ�����kO�(&4]ɹ։S��D�ʙT1D�Y�v;�,F �""�7eli8�+�Z�*� �_��Щb���?\uM?��������s7��      g   �   x�3��H��N��442"(�˘3%5��"$lld���q�pz�%���E�<.SN��Ԣ��2�!&\�}a�]/츰H��;��֋6\�sa���.컰�b7Hb;Pp���ˌ�9�(�8���`\�=... �H?      u   o  x��X�NG�O1u�&��^c ��C�B�VJ�(��*叁��^�ވЪHMp�T�jJ.M��i����"�	f^�O�G�̮m.��JQUH��ٙ9����`�žT�`_���&>�~E|0q������W?1�4?3��q~0�H�敏b"6�8��i���'�vy֜�a޸2f�9��PҬ8�ܔ��v�c���\��Y���L�r���-X�cw`Ӝc�sbb�.:Vѹ�	s4Sq�pJ�7�S�
�T��|N|!��r�eTJ�)+-Je˘/gK#�K�e��ь��&��AK�cb�3�B.��>w���9g��b<?+R�F�i%�����H��2o�f��P2n���E�\��GȾR$��-�抆c���ҽ�����8v�g)o�8=eC+�ǘ��S��\qܒ���+n��Nݞ-�w��Ɣ����g�Tʀg�'[}�]l1f�Mk:�^9���+�bŨX��L�#�QR�.���a�y�te[-��l�@�%��ZT�rW�ғ���{v��t(P��V��f��2Ɠ�e��h�����o�ZH�Ղ�fB��W ���a	�D�>`Z�wOՏ�)dC�MU���:���ڀ�ׅ<�+PL |��&۴�.û����`ك�(\m[U��D���|h
�����@�
��8��;�a�O|U������pY?�J����͠Ƴк/�
�~R��٠�+X_Ee����U�j��q#X�jUP�S.ӊ":�������@n��P���g�ѝ���OBcx�pB�[A>�O$D*O^����t��#K��!�b$��*�H��B��t��Ɠ�H;�VHa�a>�u�)@�R��FV�>���.D_��g�"��z���:.ȣ�� fK0Z/�pM�7�n{p�c��:�M�G�t��;w��Έ�!rK�+m,�N�&�����YV�#������\��45��%S�,|��ޥ����:j�����}-(DZe.�ؠ$�1�1G��q߿�_�'��Y�	{L�A�F1��>u�u� 8m���q�.��Qq������a��>BD�Q�t�ta��!���]t8�rH���g��+d��E5���|,o!�)I�
8��4�h�o:a(Z����kvA����7Rʐ4؍���*a��è-G�IES>B�i�EBNЋ]�SAS�9���h�!�)���쩯�,�9�<�UȎh�� 3�����A�ÑD	�"���;Q�w'A��|�n�I��lNE&�N%�Ut����i��ē ��ڌ���Q����}Ӥ�a��d~�D��C�X����鉍n�"1��a\�M<��W�/���?��2&���0c�ޟ���gC��P����8�)7kH�(�kT�{����瀧�S� ��T���ޛ��I!�ܜ
C� ۄ�ƇEⰨ�����jT�ݐ}O
`�-nL��@�u��X�|J�aeEU-�ۦa-��r�ՍS��Nh�S�*��:];7r~�ۚ�g�v���m�C��}Ձ�1|$X����.j{hr��R���p�v�������`�ƅ��]N��JK}��z�HC�r�Zq��yb8�(##��R�������
��]ݶ��SZ�݁��'��^E}�\��޵��mP�������}����v�O�M<zx	x��>0QEaa6?4�PߢmnjX[�w!2�Cl ����C�5�W�������Y��/��7ɹ�t��q�ݓ��\�=��KM|�L`vT�
4��D����v8,r/�P+Q3�	aC��O�N�@a+�v��g�×�z@d�[x<`�큦�'��:D)E�hh"�J)���w�3u�s��OÚ؈wx~
�em	�&x�4�c�[?��������Z      q   (   x�3�4�4�4202�5��52�2�44�4@��s��qqq �5      c   �  x�uR�NA<�|�51�YW��W?|$������d@WG����GV�	>�@Wuuu�VUU�=y�pB9�9��Њ�f�&O�����
q�	j9�@Q��:4p-�^G�G����󊼑ό�h\��j�&��ʏQF��o�+�_�
)p/t� �,a5D�9TD��)�1MibN�Nu�R�����y�+�8���h��!�mE��	t�������R&�IL9<$��!!ԔUt���n�z�;k	�"s�ǩ�,��b���m�bE�{,,d�]	]:����l!K��9��}�_2H�6Dh�3|�B7X�7��mS�=����y�Aۖ`�p'�C�n�d\����94`��MV^��[Im�g�%#W�q��%'/�ǁ�<y;�QΏ��ߏ��      o   U   x�}���0���K� &`V����('�0z[?�@qB�h�^D�Hw������+��q<f;�`�n`CK�1˚�Ǚ�s�"���.S�%�     